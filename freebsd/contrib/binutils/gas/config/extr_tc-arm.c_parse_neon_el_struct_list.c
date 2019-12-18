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
struct neon_type_el {int dummy; } ;
struct neon_typed_alias {int defined; int index; struct neon_type_el eltype; } ;
typedef  enum arm_reg_type { ____Placeholder_arm_reg_type } arm_reg_type ;

/* Variables and functions */
 int FAIL ; 
 int NEON_INTERLEAVE_LANES ; 
 int NTA_HASINDEX ; 
 int REG_TYPE_NDQ ; 
 int REG_TYPE_NQ ; 
 int SUCCESS ; 
 int /*<<< orphan*/  _ (char const* const) ; 
 int /*<<< orphan*/  first_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neon_alias_types_same (struct neon_typed_alias*,struct neon_typed_alias*) ; 
 int parse_typed_reg_or_scalar (char**,int,int*,struct neon_typed_alias*) ; 
 char** reg_expected_msgs ; 
 int skip_past_char (char**,char) ; 
 int skip_past_comma (char**) ; 

__attribute__((used)) static int
parse_neon_el_struct_list (char **str, unsigned *pbase,
                           struct neon_type_el *eltype)
{
  char *ptr = *str;
  int base_reg = -1;
  int reg_incr = -1;
  int count = 0;
  int lane = -1;
  int leading_brace = 0;
  enum arm_reg_type rtype = REG_TYPE_NDQ;
  int addregs = 1;
  const char *const incr_error = "register stride must be 1 or 2";
  const char *const type_error = "mismatched element/structure types in list";
  struct neon_typed_alias firsttype;
  
  if (skip_past_char (&ptr, '{') == SUCCESS)
    leading_brace = 1;
  
  do
    {
      struct neon_typed_alias atype;
      int getreg = parse_typed_reg_or_scalar (&ptr, rtype, &rtype, &atype);

      if (getreg == FAIL)
        {
          first_error (_(reg_expected_msgs[rtype]));
          return FAIL;
        }
      
      if (base_reg == -1)
        {
          base_reg = getreg;
          if (rtype == REG_TYPE_NQ)
            {
              reg_incr = 1;
              addregs = 2;
            }
          firsttype = atype;
        }
      else if (reg_incr == -1)
        {
          reg_incr = getreg - base_reg;
          if (reg_incr < 1 || reg_incr > 2)
            {
              first_error (_(incr_error));
              return FAIL;
            }
        }
      else if (getreg != base_reg + reg_incr * count)
        {
          first_error (_(incr_error));
          return FAIL;
        }

      if (!neon_alias_types_same (&atype, &firsttype))
        {
          first_error (_(type_error));
          return FAIL;
        }
      
      /* Handle Dn-Dm or Qn-Qm syntax. Can only be used with non-indexed list
         modes.  */
      if (ptr[0] == '-')
        {
          struct neon_typed_alias htype;
          int hireg, dregs = (rtype == REG_TYPE_NQ) ? 2 : 1;
          if (lane == -1)
            lane = NEON_INTERLEAVE_LANES;
          else if (lane != NEON_INTERLEAVE_LANES)
            {
              first_error (_(type_error));
              return FAIL;
            }
          if (reg_incr == -1)
            reg_incr = 1;
          else if (reg_incr != 1)
            {
              first_error (_("don't use Rn-Rm syntax with non-unit stride"));
              return FAIL;
            }
          ptr++;
          hireg = parse_typed_reg_or_scalar (&ptr, rtype, NULL, &htype);
          if (hireg == FAIL)
            {
              first_error (_(reg_expected_msgs[rtype]));
              return FAIL;
            }
          if (!neon_alias_types_same (&htype, &firsttype))
            {
              first_error (_(type_error));
              return FAIL;
            }
          count += hireg + dregs - getreg;
          continue;
        }
      
      /* If we're using Q registers, we can't use [] or [n] syntax.  */
      if (rtype == REG_TYPE_NQ)
        {
          count += 2;
          continue;
        }
      
      if ((atype.defined & NTA_HASINDEX) != 0)
        {
          if (lane == -1)
            lane = atype.index;
          else if (lane != atype.index)
            {
              first_error (_(type_error));
              return FAIL;
            }
        }
      else if (lane == -1)
        lane = NEON_INTERLEAVE_LANES;
      else if (lane != NEON_INTERLEAVE_LANES)
        {
          first_error (_(type_error));
          return FAIL;
        }
      count++;
    }
  while ((count != 1 || leading_brace) && skip_past_comma (&ptr) != FAIL);
  
  /* No lane set by [x]. We must be interleaving structures.  */
  if (lane == -1)
    lane = NEON_INTERLEAVE_LANES;
  
  /* Sanity check.  */
  if (lane == -1 || base_reg == -1 || count < 1 || count > 4
      || (count > 1 && reg_incr == -1))
    {
      first_error (_("error parsing element/structure list"));
      return FAIL;
    }

  if ((count > 1 || leading_brace) && skip_past_char (&ptr, '}') == FAIL)
    {
      first_error (_("expected }"));
      return FAIL;
    }
  
  if (reg_incr == -1)
    reg_incr = 1;

  if (eltype)
    *eltype = firsttype.eltype;

  *pbase = base_reg;
  *str = ptr;
  
  return lane | ((reg_incr - 1) << 4) | ((count - 1) << 5);
}