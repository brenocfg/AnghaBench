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

/* Variables and functions */
 int FAIL ; 
 int NEON_ALL_LANES ; 
 int NTA_HASINDEX ; 
 int /*<<< orphan*/  REG_TYPE_VFD ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  first_error (int /*<<< orphan*/ ) ; 
 int parse_typed_reg_or_scalar (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct neon_typed_alias*) ; 

__attribute__((used)) static int
parse_scalar (char **ccp, int elsize, struct neon_type_el *type)
{
  int reg;
  char *str = *ccp;
  struct neon_typed_alias atype;
  
  reg = parse_typed_reg_or_scalar (&str, REG_TYPE_VFD, NULL, &atype);
  
  if (reg == FAIL || (atype.defined & NTA_HASINDEX) == 0)
    return FAIL;
  
  if (atype.index == NEON_ALL_LANES)
    {
      first_error (_("scalar must have an index"));
      return FAIL;
    }
  else if (atype.index >= 64 / elsize)
    {
      first_error (_("scalar index out of range"));
      return FAIL;
    }
  
  if (type)
    *type = atype.eltype;
  
  *ccp = str;
  
  return reg * 16 + atype.index;
}