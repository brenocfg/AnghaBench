#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int old; int address; int data; } ;

/* Variables and functions */
 int SYSTEM_MD ; 
 int SYSTEM_PBC ; 
 char* arvalidchars ; 
 TYPE_1__* cheatlist ; 
 char* ggvalidchars ; 
 char* strchr (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int system_hw ; 

__attribute__((used)) static u32 decode_cheat(char *string, int index)
{
  char *p;
  int i,n;
  u32 len = 0;
  u32 address = 0;
  u16 data = 0;
  u8 ref = 0;

  /* 16-bit Game Genie code (ABCD-EFGH) */
  if ((strlen(string) >= 9) && (string[4] == '-'))
  {
    /* 16-bit system only */
    if ((system_hw & SYSTEM_PBC) != SYSTEM_MD)
    {
      return 0;
    }

    for (i = 0; i < 8; i++)
    {
      if (i == 4) string++;
      p = strchr (ggvalidchars, *string++);
      if (p == NULL) return 0;
      n = p - ggvalidchars;

      switch (i)
      {
        case 0:
        data |= n << 3;
        break;

        case 1:
        data |= n >> 2;
        address |= (n & 3) << 14;
        break;

        case 2:
        address |= n << 9;
        break;

        case 3:
        address |= (n & 0xF) << 20 | (n >> 4) << 8;
        break;
    
        case 4:
        data |= (n & 1) << 12;
        address |= (n >> 1) << 16;
        break;

        case 5:
        data |= (n & 1) << 15 | (n >> 1) << 8;
        break;

        case 6:
        data |= (n >> 3) << 13;
        address |= (n & 7) << 5;
        break;

        case 7:
        address |= n;
        break;
      }
    }

    /* code length */
    len = 9;
  }

  /* 8-bit Game Genie code (DDA-AAA-XXX) */
  else if ((strlen(string) >= 11) && (string[3] == '-') && (string[7] == '-'))
  {
    /* 8-bit system only */
    if ((system_hw & SYSTEM_PBC) == SYSTEM_MD)
    {
      return 0;
    }

    /* decode 8-bit data */
    for (i=0; i<2; i++)
    {
      p = strchr (arvalidchars, *string++);
      if (p == NULL) return 0;
      n = (p - arvalidchars) & 0xF;
      data |= (n  << ((1 - i) * 4));
    }

    /* decode 16-bit address (low 12-bits) */
    for (i=0; i<3; i++)
    {
      if (i==1) string++; /* skip separator */
      p = strchr (arvalidchars, *string++);
      if (p == NULL) return 0;
      n = (p - arvalidchars) & 0xF;
      address |= (n  << ((2 - i) * 4));
    }

    /* decode 16-bit address (high 4-bits) */
    p = strchr (arvalidchars, *string++);
    if (p == NULL) return 0;
    n = (p - arvalidchars) & 0xF;
    n ^= 0xF; /* bits inversion */
    address |= (n  << 12);

    /* RAM address are also supported */
    if (address >= 0xC000)
    {
      /* convert to 24-bit Work RAM address */
      address = 0xFF0000 | (address & 0x1FFF);
    }

    /* decode reference 8-bit data */
    for (i=0; i<2; i++)
    {
      string++; /* skip separator and 2nd digit */
      p = strchr (arvalidchars, *string++);
      if (p == NULL) return 0;
      n = (p - arvalidchars) & 0xF;
      ref |= (n  << ((1 - i) * 4));
    }
    ref = (ref >> 2) | ((ref & 0x03) << 6);  /* 2-bit right rotation */
    ref ^= 0xBA;  /* XOR */

    /* update old data value */
    cheatlist[index].old = ref;

    /* code length */
    len = 11;
  }

  /* Action Replay code */
  else if (string[6] == ':')
  {
    if ((system_hw & SYSTEM_PBC) == SYSTEM_MD)
    {
      /* 16-bit code (AAAAAA:DDDD) */
      if (strlen(string) < 11) return 0;

      /* decode 24-bit address */
      for (i=0; i<6; i++)
      {
        p = strchr (arvalidchars, *string++);
        if (p == NULL) return 0;
        n = (p - arvalidchars) & 0xF;
        address |= (n << ((5 - i) * 4));
      }

      /* decode 16-bit data */
      string++;
      for (i=0; i<4; i++)
      {
        p = strchr (arvalidchars, *string++);
        if (p == NULL) return 0;
        n = (p - arvalidchars) & 0xF;
        data |= (n << ((3 - i) * 4));
      }

      /* code length */
      len = 11;
    }
    else
    {
      /* 8-bit code (xxAAAA:DD) */
      if (strlen(string) < 9) return 0;

      /* decode 16-bit address */
      string+=2;
      for (i=0; i<4; i++)
      {
        p = strchr (arvalidchars, *string++);
        if (p == NULL) return 0;
        n = (p - arvalidchars) & 0xF;
        address |= (n << ((3 - i) * 4));
      }

      /* ROM addresses are not supported */
      if (address < 0xC000) return 0;

      /* convert to 24-bit Work RAM address */
      address = 0xFF0000 | (address & 0x1FFF);

      /* decode 8-bit data */
      string++;
      for (i=0; i<2; i++)
      {
        p = strchr (arvalidchars, *string++);
        if (p == NULL) return 0;
        n = (p - arvalidchars) & 0xF;
        data |= (n  << ((1 - i) * 4));
      }

      /* code length */
      len = 9;
    }
  }

  /* Valid code found ? */
  if (len)
  {
    /* update cheat address & data values */
    cheatlist[index].address = address;
    cheatlist[index].data = data;
  }

  /* return code length (0 = invalid) */
  return len;
}