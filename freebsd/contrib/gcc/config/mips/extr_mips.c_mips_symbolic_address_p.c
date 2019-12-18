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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int GET_MODE_SIZE (int) ; 
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

__attribute__((used)) static bool
mips_symbolic_address_p (enum mips_symbol_type symbol_type,
			 enum machine_mode mode)
{
  switch (symbol_type)
    {
    case SYMBOL_GENERAL:
      return !TARGET_MIPS16;

    case SYMBOL_SMALL_DATA:
      return true;

    case SYMBOL_CONSTANT_POOL:
      /* PC-relative addressing is only available for lw and ld.  */
      return GET_MODE_SIZE (mode) == 4 || GET_MODE_SIZE (mode) == 8;

    case SYMBOL_GOT_LOCAL:
      return true;

    case SYMBOL_GOT_GLOBAL:
      /* The address will have to be loaded from the GOT first.  */
      return false;

    case SYMBOL_GOTOFF_PAGE:
    case SYMBOL_GOTOFF_GLOBAL:
    case SYMBOL_GOTOFF_CALL:
    case SYMBOL_GOTOFF_LOADGP:
    case SYMBOL_TLS:
    case SYMBOL_TLSGD:
    case SYMBOL_TLSLDM:
    case SYMBOL_DTPREL:
    case SYMBOL_GOTTPREL:
    case SYMBOL_TPREL:
    case SYMBOL_64_HIGH:
    case SYMBOL_64_MID:
    case SYMBOL_64_LOW:
      return true;
    }
  gcc_unreachable ();
}