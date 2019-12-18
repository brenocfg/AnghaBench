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
typedef  enum reg_list_els { ____Placeholder_reg_list_els } reg_list_els ;
typedef  enum arm_reg_type { ____Placeholder_arm_reg_type } arm_reg_type ;
struct TYPE_2__ {void* error; } ;

/* Variables and functions */
 scalar_t__ ARM_CPU_HAS_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARM_MERGE_FEATURE_SETS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FAIL ; 
#define  REGLIST_NEON_D 130 
#define  REGLIST_VFP_D 129 
#define  REGLIST_VFP_S 128 
 int REG_TYPE_NDQ ; 
 int REG_TYPE_NQ ; 
 int REG_TYPE_VFD ; 
 int REG_TYPE_VFS ; 
 void* _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  arm_arch_used ; 
 int arm_typed_reg_parse (char**,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  as_tsktsk (void*) ; 
 int /*<<< orphan*/  cpu_variant ; 
 int /*<<< orphan*/  first_error (void*) ; 
 int /*<<< orphan*/  fpu_vfp_ext_v3 ; 
 void* gettext (char*) ; 
 TYPE_1__ inst ; 
 char** reg_expected_msgs ; 
 int skip_past_comma (char**) ; 
 int /*<<< orphan*/  thumb_arch_used ; 
 scalar_t__ thumb_mode ; 

__attribute__((used)) static int
parse_vfp_reg_list (char **ccp, unsigned int *pbase, enum reg_list_els etype)
{
  char *str = *ccp;
  int base_reg;
  int new_base;
  enum arm_reg_type regtype = 0;
  int max_regs = 0;
  int count = 0;
  int warned = 0;
  unsigned long mask = 0;
  int i;

  if (*str != '{')
    {
      inst.error = _("expecting {");
      return FAIL;
    }

  str++;

  switch (etype)
    {
    case REGLIST_VFP_S:
      regtype = REG_TYPE_VFS;
      max_regs = 32;
      break;
    
    case REGLIST_VFP_D:
      regtype = REG_TYPE_VFD;
      break;
    
    case REGLIST_NEON_D:
      regtype = REG_TYPE_NDQ;
      break;
    }

  if (etype != REGLIST_VFP_S)
    {
      /* VFPv3 allows 32 D registers.  */
      if (ARM_CPU_HAS_FEATURE (cpu_variant, fpu_vfp_ext_v3))
        {
          max_regs = 32;
          if (thumb_mode)
            ARM_MERGE_FEATURE_SETS (thumb_arch_used, thumb_arch_used,
                                    fpu_vfp_ext_v3);
          else
            ARM_MERGE_FEATURE_SETS (arm_arch_used, arm_arch_used,
                                    fpu_vfp_ext_v3);
        }
      else
        max_regs = 16;
    }

  base_reg = max_regs;

  do
    {
      int setmask = 1, addregs = 1;

      new_base = arm_typed_reg_parse (&str, regtype, &regtype, NULL);

      if (new_base == FAIL)
	{
	  first_error (_(reg_expected_msgs[regtype]));
	  return FAIL;
	}
 
      if (new_base >= max_regs)
        {
          first_error (_("register out of range in list"));
          return FAIL;
        }
 
      /* Note: a value of 2 * n is returned for the register Q<n>.  */
      if (regtype == REG_TYPE_NQ)
        {
          setmask = 3;
          addregs = 2;
        }

      if (new_base < base_reg)
	base_reg = new_base;

      if (mask & (setmask << new_base))
	{
	  first_error (_("invalid register list"));
	  return FAIL;
	}

      if ((mask >> new_base) != 0 && ! warned)
	{
	  as_tsktsk (_("register list not in ascending order"));
	  warned = 1;
	}

      mask |= setmask << new_base;
      count += addregs;

      if (*str == '-') /* We have the start of a range expression */
	{
	  int high_range;

	  str++;

	  if ((high_range = arm_typed_reg_parse (&str, regtype, NULL, NULL))
              == FAIL)
	    {
	      inst.error = gettext (reg_expected_msgs[regtype]);
	      return FAIL;
	    }

          if (high_range >= max_regs)
            {
              first_error (_("register out of range in list"));
              return FAIL;
            }

          if (regtype == REG_TYPE_NQ)
            high_range = high_range + 1;

	  if (high_range <= new_base)
	    {
	      inst.error = _("register range not in ascending order");
	      return FAIL;
	    }

	  for (new_base += addregs; new_base <= high_range; new_base += addregs)
	    {
	      if (mask & (setmask << new_base))
		{
		  inst.error = _("invalid register list");
		  return FAIL;
		}

	      mask |= setmask << new_base;
	      count += addregs;
	    }
	}
    }
  while (skip_past_comma (&str) != FAIL);

  str++;

  /* Sanity check -- should have raised a parse error above.  */
  if (count == 0 || count > max_regs)
    abort ();

  *pbase = base_reg;

  /* Final test -- the registers must be consecutive.  */
  mask >>= base_reg;
  for (i = 0; i < count; i++)
    {
      if ((mask & (1u << i)) == 0)
	{
	  inst.error = _("non-contiguous register range");
	  return FAIL;
	}
    }

  *ccp = str;

  return count;
}