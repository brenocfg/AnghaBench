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
struct neon_type {int elems; struct neon_type_el* el; } ;

/* Variables and functions */
 int FAIL ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  first_error (int /*<<< orphan*/ ) ; 
 scalar_t__ parse_neon_type (struct neon_type*,char**) ; 

__attribute__((used)) static int
parse_neon_operand_type (struct neon_type_el *vectype, char **ccp)
{
  char *str = *ccp;
  struct neon_type optype;

  if (*str == '.')
    {
      if (parse_neon_type (&optype, &str) == SUCCESS)
        {
          if (optype.elems == 1)
            *vectype = optype.el[0];
          else
            {
              first_error (_("only one type should be specified for operand"));
              return FAIL;
            }
        }
      else
        {
          first_error (_("vector type expected"));
          return FAIL;
        }
    }
  else
    return FAIL;
  
  *ccp = str;
  
  return SUCCESS;
}