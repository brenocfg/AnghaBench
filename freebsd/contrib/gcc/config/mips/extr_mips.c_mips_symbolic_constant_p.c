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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum mips_symbol_type { ____Placeholder_mips_symbol_type } mips_symbol_type ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  ABI_HAS_64BIT_SYMBOLS ; 
 int /*<<< orphan*/  DImode ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ LABEL_REF ; 
 int /*<<< orphan*/  Pmode ; 
 int SMALL_OPERAND (scalar_t__) ; 
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
 scalar_t__ SYMBOL_REF ; 
#define  SYMBOL_SMALL_DATA 132 
#define  SYMBOL_TLS 131 
#define  SYMBOL_TLSGD 130 
#define  SYMBOL_TLSLDM 129 
#define  SYMBOL_TPREL 128 
 scalar_t__ UNSPEC_ADDRESS_P (int /*<<< orphan*/ ) ; 
 int UNSPEC_ADDRESS_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int mips_classify_symbol (int /*<<< orphan*/ ) ; 
 int mips_offset_within_object_p (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mips_split_const (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 

bool
mips_symbolic_constant_p (rtx x, enum mips_symbol_type *symbol_type)
{
  HOST_WIDE_INT offset;

  mips_split_const (x, &x, &offset);
  if (UNSPEC_ADDRESS_P (x))
    *symbol_type = UNSPEC_ADDRESS_TYPE (x);
  else if (GET_CODE (x) == SYMBOL_REF || GET_CODE (x) == LABEL_REF)
    {
      *symbol_type = mips_classify_symbol (x);
      if (*symbol_type == SYMBOL_TLS)
	return false;
    }
  else
    return false;

  if (offset == 0)
    return true;

  /* Check whether a nonzero offset is valid for the underlying
     relocations.  */
  switch (*symbol_type)
    {
    case SYMBOL_GENERAL:
    case SYMBOL_64_HIGH:
    case SYMBOL_64_MID:
    case SYMBOL_64_LOW:
      /* If the target has 64-bit pointers and the object file only
	 supports 32-bit symbols, the values of those symbols will be
	 sign-extended.  In this case we can't allow an arbitrary offset
	 in case the 32-bit value X + OFFSET has a different sign from X.  */
      if (Pmode == DImode && !ABI_HAS_64BIT_SYMBOLS)
	return mips_offset_within_object_p (x, offset);

      /* In other cases the relocations can handle any offset.  */
      return true;

    case SYMBOL_CONSTANT_POOL:
      /* Allow constant pool references to be converted to LABEL+CONSTANT.
	 In this case, we no longer have access to the underlying constant,
	 but the original symbol-based access was known to be valid.  */
      if (GET_CODE (x) == LABEL_REF)
	return true;

      /* Fall through.  */

    case SYMBOL_SMALL_DATA:
      /* Make sure that the offset refers to something within the
	 underlying object.  This should guarantee that the final
	 PC- or GP-relative offset is within the 16-bit limit.  */
      return mips_offset_within_object_p (x, offset);

    case SYMBOL_GOT_LOCAL:
    case SYMBOL_GOTOFF_PAGE:
      /* The linker should provide enough local GOT entries for a
	 16-bit offset.  Larger offsets may lead to GOT overflow.  */
      return SMALL_OPERAND (offset);

    case SYMBOL_GOT_GLOBAL:
    case SYMBOL_GOTOFF_GLOBAL:
    case SYMBOL_GOTOFF_CALL:
    case SYMBOL_GOTOFF_LOADGP:
    case SYMBOL_TLSGD:
    case SYMBOL_TLSLDM:
    case SYMBOL_DTPREL:
    case SYMBOL_TPREL:
    case SYMBOL_GOTTPREL:
    case SYMBOL_TLS:
      return false;
    }
  gcc_unreachable ();
}