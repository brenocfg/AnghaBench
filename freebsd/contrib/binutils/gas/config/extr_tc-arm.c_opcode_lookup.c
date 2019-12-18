#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct asm_opcode {int tag; } ;
struct asm_cond {void* value; } ;
typedef  scalar_t__ bfd_boolean ;
struct TYPE_3__ {scalar_t__ elems; } ;
struct TYPE_4__ {int size_req; void* cond; int /*<<< orphan*/  error; TYPE_1__ vectype; } ;

/* Variables and functions */
 scalar_t__ ARM_CPU_HAS_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BAD_COND ; 
 void* COND_ALWAYS ; 
 scalar_t__ FAIL ; 
#define  OT_cinfix3 136 
#define  OT_cinfix3_deprecated 135 
#define  OT_cinfix3_legacy 134 
#define  OT_csuf_or_in3 133 
#define  OT_csuffix 132 
#define  OT_csuffixF 131 
 int OT_odd_infix_0 ; 
#define  OT_odd_infix_unc 130 
#define  OT_unconditional 129 
#define  OT_unconditionalF 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  arm_cond_hsh ; 
 int /*<<< orphan*/  arm_ops_hsh ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (struct asm_cond const*) ; 
 int /*<<< orphan*/  cpu_variant ; 
 int /*<<< orphan*/  fpu_neon_ext_v1 ; 
 void* hash_find_n (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__ inst ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 scalar_t__ parse_neon_type (TYPE_1__*,char**) ; 
 int /*<<< orphan*/  thumb_mode ; 
 scalar_t__ unified_syntax ; 

__attribute__((used)) static const struct asm_opcode *
opcode_lookup (char **str)
{
  char *end, *base;
  char *affix;
  const struct asm_opcode *opcode;
  const struct asm_cond *cond;
  char save[2];
  bfd_boolean neon_supported;
  
  neon_supported = ARM_CPU_HAS_FEATURE (cpu_variant, fpu_neon_ext_v1);

  /* Scan up to the end of the mnemonic, which must end in white space,
     '.' (in unified mode, or for Neon instructions), or end of string.  */
  for (base = end = *str; *end != '\0'; end++)
    if (*end == ' ' || ((unified_syntax || neon_supported) && *end == '.'))
      break;

  if (end == base)
    return 0;

  /* Handle a possible width suffix and/or Neon type suffix.  */
  if (end[0] == '.')
    {
      int offset = 2;
      
      /* The .w and .n suffixes are only valid if the unified syntax is in
         use.  */
      if (unified_syntax && end[1] == 'w')
	inst.size_req = 4;
      else if (unified_syntax && end[1] == 'n')
	inst.size_req = 2;
      else
        offset = 0;

      inst.vectype.elems = 0;

      *str = end + offset;

      if (end[offset] == '.')      
	{
	  /* See if we have a Neon type suffix (possible in either unified or
             non-unified ARM syntax mode).  */
          if (parse_neon_type (&inst.vectype, str) == FAIL)
	    return 0;
        }
      else if (end[offset] != '\0' && end[offset] != ' ')
        return 0;
    }
  else
    *str = end;

  /* Look for unaffixed or special-case affixed mnemonic.  */
  opcode = hash_find_n (arm_ops_hsh, base, end - base);
  if (opcode)
    {
      /* step U */
      if (opcode->tag < OT_odd_infix_0)
	{
	  inst.cond = COND_ALWAYS;
	  return opcode;
	}

      if (unified_syntax)
	as_warn (_("conditional infixes are deprecated in unified syntax"));
      affix = base + (opcode->tag - OT_odd_infix_0);
      cond = hash_find_n (arm_cond_hsh, affix, 2);
      assert (cond);

      inst.cond = cond->value;
      return opcode;
    }

  /* Cannot have a conditional suffix on a mnemonic of less than two
     characters.  */
  if (end - base < 3)
    return 0;

  /* Look for suffixed mnemonic.  */
  affix = end - 2;
  cond = hash_find_n (arm_cond_hsh, affix, 2);
  opcode = hash_find_n (arm_ops_hsh, base, affix - base);
  if (opcode && cond)
    {
      /* step CE */
      switch (opcode->tag)
	{
	case OT_cinfix3_legacy:
	  /* Ignore conditional suffixes matched on infix only mnemonics.  */
	  break;

	case OT_cinfix3:
	case OT_cinfix3_deprecated:
	case OT_odd_infix_unc:
	  if (!unified_syntax)
	    return 0;
	  /* else fall through */

	case OT_csuffix:
        case OT_csuffixF:
	case OT_csuf_or_in3:
	  inst.cond = cond->value;
	  return opcode;

	case OT_unconditional:
	case OT_unconditionalF:
	  if (thumb_mode)
	    {
	      inst.cond = cond->value;
	    }
	  else
	    {
	      /* delayed diagnostic */
	      inst.error = BAD_COND;
	      inst.cond = COND_ALWAYS;
	    }
	  return opcode;

	default:
	  return 0;
	}
    }

  /* Cannot have a usual-position infix on a mnemonic of less than
     six characters (five would be a suffix).  */
  if (end - base < 6)
    return 0;

  /* Look for infixed mnemonic in the usual position.  */
  affix = base + 3;
  cond = hash_find_n (arm_cond_hsh, affix, 2);
  if (!cond)
    return 0;

  memcpy (save, affix, 2);
  memmove (affix, affix + 2, (end - affix) - 2);
  opcode = hash_find_n (arm_ops_hsh, base, (end - base) - 2);
  memmove (affix + 2, affix, (end - affix) - 2);
  memcpy (affix, save, 2);

  if (opcode
      && (opcode->tag == OT_cinfix3
	  || opcode->tag == OT_cinfix3_deprecated
	  || opcode->tag == OT_csuf_or_in3
	  || opcode->tag == OT_cinfix3_legacy))
    {
      /* step CM */
      if (unified_syntax
	  && (opcode->tag == OT_cinfix3
	      || opcode->tag == OT_cinfix3_deprecated))
	as_warn (_("conditional infixes are deprecated in unified syntax"));

      inst.cond = cond->value;
      return opcode;
    }

  return 0;
}