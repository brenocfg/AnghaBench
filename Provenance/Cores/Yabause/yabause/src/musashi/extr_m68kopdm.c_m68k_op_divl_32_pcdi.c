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
typedef  int uint64 ;
typedef  int uint ;
typedef  scalar_t__ sint64 ;
typedef  scalar_t__ sint32 ;
typedef  int sint ;

/* Variables and functions */
 scalar_t__ BIT_A (int) ; 
 scalar_t__ BIT_B (int) ; 
 int /*<<< orphan*/  CFLAG_CLEAR ; 
 int /*<<< orphan*/  CPU_TYPE ; 
 scalar_t__ CPU_TYPE_IS_EC020_PLUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXCEPTION_ZERO_DIVIDE ; 
 int /*<<< orphan*/  FLAG_C ; 
 int /*<<< orphan*/  FLAG_N ; 
 int /*<<< orphan*/  FLAG_V ; 
 int FLAG_Z ; 
 int GET_MSB_32 (int) ; 
 int MAKE_INT_32 (int) ; 
 int MASK_OUT_ABOVE_32 (int) ; 
 int /*<<< orphan*/  NFLAG_32 (int) ; 
 int /*<<< orphan*/  NFLAG_SET ; 
 int OPER_I_16 () ; 
 int OPER_PCDI_32 () ; 
 int* REG_D ; 
 int /*<<< orphan*/  VFLAG_CLEAR ; 
 int /*<<< orphan*/  VFLAG_SET ; 
 int ZFLAG_CLEAR ; 
 int /*<<< orphan*/  m68ki_exception_illegal () ; 
 int /*<<< orphan*/  m68ki_exception_trap (int /*<<< orphan*/ ) ; 

void m68k_op_divl_32_pcdi(void)
{
#if M68K_USE_64_BIT

	if(CPU_TYPE_IS_EC020_PLUS(CPU_TYPE))
	{
		uint word2 = OPER_I_16();
		uint64 divisor = OPER_PCDI_32();
		uint64 dividend  = 0;
		uint64 quotient  = 0;
		uint64 remainder = 0;

		if(divisor != 0)
		{
			if(BIT_A(word2))	/* 64 bit */
			{
				dividend = REG_D[word2 & 7];
				dividend <<= 32;
				dividend |= REG_D[(word2 >> 12) & 7];

				if(BIT_B(word2))	   /* signed */
				{
					quotient  = (uint64)((sint64)dividend / (sint64)((sint32)divisor));
					remainder = (uint64)((sint64)dividend % (sint64)((sint32)divisor));
					if((sint64)quotient != (sint64)((sint32)quotient))
					{
						FLAG_V = VFLAG_SET;
						return;
					}
				}
				else					/* unsigned */
				{
					quotient = dividend / divisor;
					if(quotient > 0xffffffff)
					{
						FLAG_V = VFLAG_SET;
						return;
					}
					remainder = dividend % divisor;
				}
			}
			else	/* 32 bit */
			{
				dividend = REG_D[(word2 >> 12) & 7];
				if(BIT_B(word2))	   /* signed */
				{
					quotient  = (uint64)((sint64)((sint32)dividend) / (sint64)((sint32)divisor));
					remainder = (uint64)((sint64)((sint32)dividend) % (sint64)((sint32)divisor));
				}
				else					/* unsigned */
				{
					quotient = dividend / divisor;
					remainder = dividend % divisor;
				}
			}

			REG_D[word2 & 7] = remainder;
			REG_D[(word2 >> 12) & 7] = quotient;

			FLAG_N = NFLAG_32(quotient);
			FLAG_Z = quotient;
			FLAG_V = VFLAG_CLEAR;
			FLAG_C = CFLAG_CLEAR;
			return;
		}
		m68ki_exception_trap(EXCEPTION_ZERO_DIVIDE);
		return;
	}
	m68ki_exception_illegal();

#else

	if(CPU_TYPE_IS_EC020_PLUS(CPU_TYPE))
	{
		uint word2 = OPER_I_16();
		uint divisor = OPER_PCDI_32();
		uint dividend_hi = REG_D[word2 & 7];
		uint dividend_lo = REG_D[(word2 >> 12) & 7];
		uint quotient = 0;
		uint remainder = 0;
		uint dividend_neg = 0;
		uint divisor_neg = 0;
		sint i;
		uint overflow;

		if(divisor != 0)
		{
			/* quad / long : long quotient, long remainder */
			if(BIT_A(word2))
			{
				if(BIT_B(word2))	   /* signed */
				{
					/* special case in signed divide */
					if(dividend_hi == 0 && dividend_lo == 0x80000000 && divisor == 0xffffffff)
					{
						REG_D[word2 & 7] = 0;
						REG_D[(word2 >> 12) & 7] = 0x80000000;

						FLAG_N = NFLAG_SET;
						FLAG_Z = ZFLAG_CLEAR;
						FLAG_V = VFLAG_CLEAR;
						FLAG_C = CFLAG_CLEAR;
						return;
					}
					if(GET_MSB_32(dividend_hi))
					{
						dividend_neg = 1;
						dividend_hi = (uint)MASK_OUT_ABOVE_32((-(sint)dividend_hi) - (dividend_lo != 0));
						dividend_lo = (uint)MASK_OUT_ABOVE_32(-(sint)dividend_lo);
					}
					if(GET_MSB_32(divisor))
					{
						divisor_neg = 1;
						divisor = (uint)MASK_OUT_ABOVE_32(-(sint)divisor);

					}
				}

				/* if the upper long is greater than the divisor, we're overflowing. */
				if(dividend_hi >= divisor)
				{
					FLAG_V = VFLAG_SET;
					return;
				}

				for(i = 31; i >= 0; i--)
				{
					quotient <<= 1;
					remainder = (remainder << 1) + ((dividend_hi >> i) & 1);
					if(remainder >= divisor)
					{
						remainder -= divisor;
						quotient++;
					}
				}
				for(i = 31; i >= 0; i--)
				{
					quotient <<= 1;
					overflow = GET_MSB_32(remainder);
					remainder = (remainder << 1) + ((dividend_lo >> i) & 1);
					if(remainder >= divisor || overflow)
					{
						remainder -= divisor;
						quotient++;
					}
				}

				if(BIT_B(word2))	   /* signed */
				{
					if(quotient > 0x7fffffff)
					{
						FLAG_V = VFLAG_SET;
						return;
					}
					if(dividend_neg)
					{
						remainder = (uint)MASK_OUT_ABOVE_32(-(sint)remainder);
						quotient = (uint)MASK_OUT_ABOVE_32(-(sint)quotient);
					}
					if(divisor_neg)
						quotient = (uint)MASK_OUT_ABOVE_32(-(sint)quotient);
				}

				REG_D[word2 & 7] = remainder;
				REG_D[(word2 >> 12) & 7] = quotient;

				FLAG_N = NFLAG_32(quotient);
				FLAG_Z = quotient;
				FLAG_V = VFLAG_CLEAR;
				FLAG_C = CFLAG_CLEAR;
				return;
			}

			/* long / long: long quotient, maybe long remainder */
			if(BIT_B(word2))	   /* signed */
			{
				/* Special case in divide */
				if(dividend_lo == 0x80000000 && divisor == 0xffffffff)
				{
					FLAG_N = NFLAG_SET;
					FLAG_Z = ZFLAG_CLEAR;
					FLAG_V = VFLAG_CLEAR;
					FLAG_C = CFLAG_CLEAR;
					REG_D[(word2 >> 12) & 7] = 0x80000000;
					REG_D[word2 & 7] = 0;
					return;
				}
				REG_D[word2 & 7] = MAKE_INT_32(dividend_lo) % MAKE_INT_32(divisor);
				quotient = REG_D[(word2 >> 12) & 7] = MAKE_INT_32(dividend_lo) / MAKE_INT_32(divisor);
			}
			else
			{
				REG_D[word2 & 7] = MASK_OUT_ABOVE_32(dividend_lo) % MASK_OUT_ABOVE_32(divisor);
				quotient = REG_D[(word2 >> 12) & 7] = MASK_OUT_ABOVE_32(dividend_lo) / MASK_OUT_ABOVE_32(divisor);
			}

			FLAG_N = NFLAG_32(quotient);
			FLAG_Z = quotient;
			FLAG_V = VFLAG_CLEAR;
			FLAG_C = CFLAG_CLEAR;
			return;
		}
		m68ki_exception_trap(EXCEPTION_ZERO_DIVIDE);
		return;
	}
	m68ki_exception_illegal();

#endif
}