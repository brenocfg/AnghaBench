#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct reg_entry {scalar_t__ type; int number; struct neon_typed_alias* neon; } ;
struct neon_type_el {int size; int /*<<< orphan*/  type; } ;
struct neon_typed_alias {int defined; int index; struct neon_type_el eltype; } ;
struct TYPE_3__ {scalar_t__ X_op; int X_add_number; } ;
typedef  TYPE_1__ expressionS ;
typedef  enum arm_reg_type { ____Placeholder_arm_reg_type } arm_reg_type ;

/* Variables and functions */
 int FAIL ; 
 int /*<<< orphan*/  GE_NO_PREFIX ; 
 int NEON_ALL_LANES ; 
 int NTA_HASINDEX ; 
 int NTA_HASTYPE ; 
 int /*<<< orphan*/  NT_invtype ; 
 scalar_t__ O_constant ; 
 int REG_TYPE_MMXWC ; 
 scalar_t__ REG_TYPE_MMXWCG ; 
 int REG_TYPE_NDQ ; 
 scalar_t__ REG_TYPE_NQ ; 
 int REG_TYPE_NSDQ ; 
 scalar_t__ REG_TYPE_VFD ; 
 scalar_t__ REG_TYPE_VFS ; 
 int REG_TYPE_VFSD ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int arm_reg_alt_syntax (char**,char*,struct reg_entry*,int) ; 
 struct reg_entry* arm_reg_parse_multi (char**) ; 
 int /*<<< orphan*/  first_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_get_expression (TYPE_1__*,char**,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_neon_operand_type (struct neon_type_el*,char**) ; 
 int skip_past_char (char**,char) ; 

__attribute__((used)) static int
parse_typed_reg_or_scalar (char **ccp, enum arm_reg_type type,
                           enum arm_reg_type *rtype,
                           struct neon_typed_alias *typeinfo)
{
  char *str = *ccp;
  struct reg_entry *reg = arm_reg_parse_multi (&str);
  struct neon_typed_alias atype;
  struct neon_type_el parsetype;

  atype.defined = 0;
  atype.index = -1;
  atype.eltype.type = NT_invtype;
  atype.eltype.size = -1;

  /* Try alternate syntax for some types of register. Note these are mutually
     exclusive with the Neon syntax extensions.  */
  if (reg == NULL)
    {
      int altreg = arm_reg_alt_syntax (&str, *ccp, reg, type);
      if (altreg != FAIL)
        *ccp = str;
      if (typeinfo)
        *typeinfo = atype;
      return altreg;
    }

  /* Undo polymorphism when a set of register types may be accepted.  */
  if ((type == REG_TYPE_NDQ
       && (reg->type == REG_TYPE_NQ || reg->type == REG_TYPE_VFD))
      || (type == REG_TYPE_VFSD
          && (reg->type == REG_TYPE_VFS || reg->type == REG_TYPE_VFD))
      || (type == REG_TYPE_NSDQ
          && (reg->type == REG_TYPE_VFS || reg->type == REG_TYPE_VFD
              || reg->type == REG_TYPE_NQ))
      || (type == REG_TYPE_MMXWC
	  && (reg->type == REG_TYPE_MMXWCG)))
    type = reg->type;

  if (type != reg->type)
    return FAIL;

  if (reg->neon)
    atype = *reg->neon;
  
  if (parse_neon_operand_type (&parsetype, &str) == SUCCESS)
    {
      if ((atype.defined & NTA_HASTYPE) != 0)
        {
          first_error (_("can't redefine type for operand"));
          return FAIL;
        }
      atype.defined |= NTA_HASTYPE;
      atype.eltype = parsetype;
    }
    
  if (skip_past_char (&str, '[') == SUCCESS)
    {
      if (type != REG_TYPE_VFD)
        {
          first_error (_("only D registers may be indexed"));
          return FAIL;
        }
    
      if ((atype.defined & NTA_HASINDEX) != 0)
        {
          first_error (_("can't change index for operand"));
          return FAIL;
        }

      atype.defined |= NTA_HASINDEX;

      if (skip_past_char (&str, ']') == SUCCESS)
        atype.index = NEON_ALL_LANES;
      else
        {
          expressionS exp;

          my_get_expression (&exp, &str, GE_NO_PREFIX);

          if (exp.X_op != O_constant)
            {
              first_error (_("constant expression required"));
              return FAIL;
            }

          if (skip_past_char (&str, ']') == FAIL)
            return FAIL;

          atype.index = exp.X_add_number;
        }
    }
  
  if (typeinfo)
    *typeinfo = atype;
  
  if (rtype)
    *rtype = type;
  
  *ccp = str;
  
  return reg->number;
}