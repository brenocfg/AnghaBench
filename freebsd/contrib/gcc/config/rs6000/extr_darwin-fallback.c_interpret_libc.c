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
typedef  int uint32_t ;
struct _Unwind_Context {int dummy; } ;
typedef  int reg_unit ;
typedef  int int32_t ;
typedef  int int16_t ;

/* Variables and functions */
 int CR2_REGNO ; 
 int _Unwind_GetCFA (struct _Unwind_Context*) ; 
 int _Unwind_GetGR (struct _Unwind_Context*,int) ; 
 scalar_t__ _Unwind_GetIP (struct _Unwind_Context*) ; 

__attribute__((used)) static bool
interpret_libc (reg_unit gprs[32], struct _Unwind_Context *context)
{
  uint32_t *pc = (uint32_t *)_Unwind_GetIP (context);
  uint32_t cr;
  reg_unit lr = (reg_unit) pc;
  reg_unit ctr = 0;
  uint32_t *invalid_address = NULL;

  int i;

  for (i = 0; i < 13; i++)
    gprs[i] = 1;
  gprs[1] = _Unwind_GetCFA (context);
  for (; i < 32; i++)
    gprs[i] = _Unwind_GetGR (context, i);
  cr = _Unwind_GetGR (context, CR2_REGNO);

  /* For each supported Libc, we have to track the code flow
     all the way back into the kernel.
  
     This code is believed to support all released Libc/Libsystem builds since
     Jaguar 6C115, including all the security updates.  To be precise,

     Libc	Libsystem	Build(s)
     262~1	60~37		6C115
     262~1	60.2~4		6D52
     262~1	61~3		6F21-6F22
     262~1	63~24		6G30-6G37
     262~1	63~32		6I34-6I35
     262~1	63~64		6L29-6L60
     262.4.1~1	63~84		6L123-6R172
     
     320~1	71~101		7B85-7D28
     320~1	71~266		7F54-7F56
     320~1	71~288		7F112
     320~1	71~289		7F113
     320.1.3~1	71.1.1~29	7H60-7H105
     320.1.3~1	71.1.1~30	7H110-7H113
     320.1.3~1	71.1.1~31	7H114
     
     That's a big table!  It would be insane to try to keep track of
     every little detail, so we just read the code itself and do what
     it would do.
  */

  for (;;)
    {
      uint32_t ins = *pc++;
      
      if ((ins & 0xFC000003) == 0x48000000)  /* b instruction */
	{
	  pc += ((((int32_t) ins & 0x3FFFFFC) ^ 0x2000000) - 0x2000004) / 4;
	  continue;
	}
      if ((ins & 0xFC600000) == 0x2C000000)  /* cmpwi */
	{
	  int32_t val1 = (int16_t) ins;
	  int32_t val2 = gprs[ins >> 16 & 0x1F];
	  /* Only beq and bne instructions are supported, so we only
	     need to set the EQ bit.  */
	  uint32_t mask = 0xF << ((ins >> 21 & 0x1C) ^ 0x1C);
	  if (val1 == val2)
	    cr |= mask;
	  else
	    cr &= ~mask;
	  continue;
	}
      if ((ins & 0xFEC38003) == 0x40820000)  /* forwards beq/bne */
	{
	  if ((cr >> ((ins >> 16 & 0x1F) ^ 0x1F) & 1) == (ins >> 24 & 1))
	    pc += (ins & 0x7FFC) / 4 - 1;
	  continue;
	}
      if ((ins & 0xFC0007FF) == 0x7C000378) /* or, including mr */
	{
	  gprs [ins >> 16 & 0x1F] = (gprs [ins >> 11 & 0x1F] 
				     | gprs [ins >> 21 & 0x1F]);
	  continue;
	}
      if (ins >> 26 == 0x0E)  /* addi, including li */
	{
	  reg_unit src = (ins >> 16 & 0x1F) == 0 ? 0 : gprs [ins >> 16 & 0x1F];
	  gprs [ins >> 21 & 0x1F] = src + (int16_t) ins;
	  continue;
	}
      if (ins >> 26 == 0x0F)  /* addis, including lis */
	{
	  reg_unit src = (ins >> 16 & 0x1F) == 0 ? 0 : gprs [ins >> 16 & 0x1F];
	  gprs [ins >> 21 & 0x1F] = src + ((int16_t) ins << 16);
	  continue;
	}
      if (ins >> 26 == 0x20)  /* lwz */
	{
	  reg_unit src = (ins >> 16 & 0x1F) == 0 ? 0 : gprs [ins >> 16 & 0x1F];
	  uint32_t *p = (uint32_t *)(src + (int16_t) ins);
	  if (p == invalid_address)
	    return false;
	  gprs [ins >> 21 & 0x1F] = *p;
	  continue;
	}
      if (ins >> 26 == 0x21)  /* lwzu */
	{
	  uint32_t *p = (uint32_t *)(gprs [ins >> 16 & 0x1F] += (int16_t) ins);
	  if (p == invalid_address)
	    return false;
	  gprs [ins >> 21 & 0x1F] = *p;
	  continue;
	}
      if (ins >> 26 == 0x24)  /* stw */
	/* What we hope this is doing is '--in_sigtramp'.  We don't want
	   to actually store to memory, so just make a note of the
	   address and refuse to load from it.  */
	{
	  reg_unit src = (ins >> 16 & 0x1F) == 0 ? 0 : gprs [ins >> 16 & 0x1F];
	  uint32_t *p = (uint32_t *)(src + (int16_t) ins);
	  if (p == NULL || invalid_address != NULL)
	    return false;
	  invalid_address = p;
	  continue;
	}
      if (ins >> 26 == 0x2E) /* lmw */
	{
	  reg_unit src = (ins >> 16 & 0x1F) == 0 ? 0 : gprs [ins >> 16 & 0x1F];
	  uint32_t *p = (uint32_t *)(src + (int16_t) ins);
	  int i;

	  for (i = (ins >> 21 & 0x1F); i < 32; i++)
	    {
	      if (p == invalid_address)
		return false;
	      gprs[i] = *p++;
	    }
	  continue;
	}
      if ((ins & 0xFC1FFFFF) == 0x7c0803a6)  /* mtlr */
	{
	  lr = gprs [ins >> 21 & 0x1F];
	  continue;
	}
      if ((ins & 0xFC1FFFFF) == 0x7c0802a6)  /* mflr */
	{
	  gprs [ins >> 21 & 0x1F] = lr;
	  continue;
	}
      if ((ins & 0xFC1FFFFF) == 0x7c0903a6)  /* mtctr */
	{
	  ctr = gprs [ins >> 21 & 0x1F];
	  continue;
	}
      /* The PowerPC User's Manual says that bit 11 of the mtcrf
	 instruction is reserved and should be set to zero, but it
	 looks like the Darwin assembler doesn't do that... */
      if ((ins & 0xFC000FFF) == 0x7c000120) /* mtcrf */
	{
	  int i;
	  uint32_t mask = 0;
	  for (i = 0; i < 8; i++)
	    mask |= ((-(ins >> (12 + i) & 1)) & 0xF) << 4 * i;
	  cr = (cr & ~mask) | (gprs [ins >> 21 & 0x1F] & mask);
	  continue;
	}
      if (ins == 0x429f0005)  /* bcl- 20,4*cr7+so,.+4, loads pc into LR */
	{
	  lr = (reg_unit) pc;
	  continue;
	}
      if (ins == 0x4e800420) /* bctr */
	{
	  pc = (uint32_t *) ctr;
	  continue;
	}
      if (ins == 0x44000002) /* sc */
	return true;

      return false;
    }
}