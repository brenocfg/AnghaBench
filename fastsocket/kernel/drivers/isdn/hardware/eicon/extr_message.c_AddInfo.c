#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t byte ;

/* Variables and functions */
 size_t MAX_MULTI_IE ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,size_t) ; 

__attribute__((used)) static byte AddInfo(byte   **add_i,
                    byte   **fty_i,
                    byte   *esc_chi,
                    byte *facility)
{
  byte i;
  byte j;
  byte k;
  byte flen;
  byte len=0;
   /* facility is a nested structure */
   /* FTY can be more than once      */

	if (esc_chi[0] && !(esc_chi[esc_chi[0]] & 0x7f))
  {
    add_i[0] = (byte   *)"\x02\x02\x00"; /* use neither b nor d channel */
  }

  else
  {
    add_i[0] = (byte   *)"";
  }
  if(!fty_i[0][0])
  {
    add_i[3] = (byte   *)"";
  }
  else
  {    /* facility array found  */
    for(i=0,j=1;i<MAX_MULTI_IE && fty_i[i][0];i++)
    {
      dbug(1,dprintf("AddIFac[%d]",fty_i[i][0]));
      len += fty_i[i][0];
      len += 2;
      flen=fty_i[i][0];
      facility[j++]=0x1c; /* copy fac IE */
      for(k=0;k<=flen;k++,j++)
      {
        facility[j]=fty_i[i][k];
/*      dbug(1,dprintf("%x ",facility[j])); */
      }
    }
    facility[0] = len;
    add_i[3] = facility;
  }
/*  dbug(1,dprintf("FacArrLen=%d ",len)); */
  len = add_i[0][0]+add_i[1][0]+add_i[2][0]+add_i[3][0];
  len += 4;                          /* calculate length of all */
  return(len);
}