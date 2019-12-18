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
typedef  enum mips_symbol_type { ____Placeholder_mips_symbol_type } mips_symbol_type ;

/* Variables and functions */
 int /*<<< orphan*/  ABI_HAS_64BIT_SYMBOLS ; 
#define  SYMBOL_64_HIGH 145 
#define  SYMBOL_64_LOW 144 
#define  SYMBOL_64_MID 143 
#define  SYMBOL_CONSTANT_POOL 142 
#define  SYMBOL_DTPREL 141 
#define  SYMBOL_GENERAL 140 
#define  SYMBOL_GOTOFF_CALL 139 
#define  SYMBOL_GOTOFF_GLOBAL 138 
#define  SYMBOL_GOTOFF_LOADGP 137 
#define  SYMBOL_GOTOFF_PAGE 136 
#define  SYMBOL_GOTTPREL 135 
#define  SYMBOL_GOT_GLOBAL 134 
#define  SYMBOL_GOT_LOCAL 133 
#define  SYMBOL_SMALL_DATA 132 
#define  SYMBOL_TLS 131 
#define  SYMBOL_TLSGD 130 
#define  SYMBOL_TLSLDM 129 
#define  SYMBOL_TPREL 128 
 int /*<<< orphan*/  TARGET_MIPS16 ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/ * mips_split_p ; 

__attribute__((used)) static int
mips_symbol_insns (enum mips_symbol_type type)
{
  switch (type)
    {
    case SYMBOL_GENERAL:
      /* In mips16 code, general symbols must be fetched from the
	 constant pool.  */
      if (TARGET_MIPS16)
	return 0;

      /* When using 64-bit symbols, we need 5 preparatory instructions,
	 such as:

	     lui     $at,%highest(symbol)
	     daddiu  $at,$at,%higher(symbol)
	     dsll    $at,$at,16
	     daddiu  $at,$at,%hi(symbol)
	     dsll    $at,$at,16

	 The final address is then $at + %lo(symbol).  With 32-bit
	 symbols we just need a preparatory lui.  */
      return (ABI_HAS_64BIT_SYMBOLS ? 6 : 2);

    case SYMBOL_SMALL_DATA:
      return 1;

    case SYMBOL_CONSTANT_POOL:
      /* This case is for mips16 only.  Assume we'll need an
	 extended instruction.  */
      return 2;

    case SYMBOL_GOT_LOCAL:
    case SYMBOL_GOT_GLOBAL:
      /* Unless -funit-at-a-time is in effect, we can't be sure whether
	 the local/global classification is accurate.  See override_options
	 for details.

	 The worst cases are:

	 (1) For local symbols when generating o32 or o64 code.  The assembler
	     will use:

		 lw	      $at,%got(symbol)
		 nop

	     ...and the final address will be $at + %lo(symbol).

	 (2) For global symbols when -mxgot.  The assembler will use:

	         lui     $at,%got_hi(symbol)
	         (d)addu $at,$at,$gp

	     ...and the final address will be $at + %got_lo(symbol).  */
      return 3;

    case SYMBOL_GOTOFF_PAGE:
    case SYMBOL_GOTOFF_GLOBAL:
    case SYMBOL_GOTOFF_CALL:
    case SYMBOL_GOTOFF_LOADGP:
    case SYMBOL_64_HIGH:
    case SYMBOL_64_MID:
    case SYMBOL_64_LOW:
    case SYMBOL_TLSGD:
    case SYMBOL_TLSLDM:
    case SYMBOL_DTPREL:
    case SYMBOL_GOTTPREL:
    case SYMBOL_TPREL:
      /* Check whether the offset is a 16- or 32-bit value.  */
      return mips_split_p[type] ? 2 : 1;

    case SYMBOL_TLS:
      /* We don't treat a bare TLS symbol as a constant.  */
      return 0;
    }
  gcc_unreachable ();
}