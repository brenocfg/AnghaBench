#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct reg_entry {int type; int number; struct neon_typed_alias* neon; } ;
struct TYPE_4__ {int size; int /*<<< orphan*/  type; } ;
struct neon_typed_alias {int defined; int index; TYPE_1__ eltype; } ;
struct neon_type {int elems; TYPE_1__* el; } ;
struct TYPE_5__ {scalar_t__ X_op; int X_add_number; } ;
typedef  TYPE_2__ expressionS ;
typedef  enum arm_reg_type { ____Placeholder_arm_reg_type } arm_reg_type ;

/* Variables and functions */
 scalar_t__ FAIL ; 
 int /*<<< orphan*/  GE_NO_PREFIX ; 
 int NTA_HASINDEX ; 
 int NTA_HASTYPE ; 
 int /*<<< orphan*/  NT_invtype ; 
 scalar_t__ O_constant ; 
 int REG_TYPE_NQ ; 
 int REG_TYPE_VFD ; 
 scalar_t__ SUCCESS ; 
 char TOLOWER (char) ; 
 char TOUPPER (char) ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* alloca (int) ; 
 struct reg_entry* arm_reg_parse_multi (char**) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_neon_reg_alias (char*,int,int,struct neon_typed_alias*) ; 
 int /*<<< orphan*/  my_get_expression (TYPE_2__*,char**,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_neon_type (struct neon_type*,char**) ; 
 scalar_t__ skip_past_char (char**,char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static int
create_neon_reg_alias (char *newname, char *p)
{
  enum arm_reg_type basetype;
  struct reg_entry *basereg;
  struct reg_entry mybasereg;
  struct neon_type ntype;
  struct neon_typed_alias typeinfo;
  char *namebuf, *nameend;
  int namelen;
  
  typeinfo.defined = 0;
  typeinfo.eltype.type = NT_invtype;
  typeinfo.eltype.size = -1;
  typeinfo.index = -1;
  
  nameend = p;
  
  if (strncmp (p, " .dn ", 5) == 0)
    basetype = REG_TYPE_VFD;
  else if (strncmp (p, " .qn ", 5) == 0)
    basetype = REG_TYPE_NQ;
  else
    return 0;
  
  p += 5;
  
  if (*p == '\0')
    return 0;
  
  basereg = arm_reg_parse_multi (&p);

  if (basereg && basereg->type != basetype)
    {
      as_bad (_("bad type for register"));
      return 0;
    }

  if (basereg == NULL)
    {
      expressionS exp;
      /* Try parsing as an integer.  */
      my_get_expression (&exp, &p, GE_NO_PREFIX);
      if (exp.X_op != O_constant)
        {
          as_bad (_("expression must be constant"));
          return 0;
        }
      basereg = &mybasereg;
      basereg->number = (basetype == REG_TYPE_NQ) ? exp.X_add_number * 2
                                                  : exp.X_add_number;
      basereg->neon = 0;
    }

  if (basereg->neon)
    typeinfo = *basereg->neon;

  if (parse_neon_type (&ntype, &p) == SUCCESS)
    {
      /* We got a type.  */
      if (typeinfo.defined & NTA_HASTYPE)
        {
          as_bad (_("can't redefine the type of a register alias"));
          return 0;
        }
      
      typeinfo.defined |= NTA_HASTYPE;
      if (ntype.elems != 1)
        {
          as_bad (_("you must specify a single type only"));
          return 0;
        }
      typeinfo.eltype = ntype.el[0];
    }
  
  if (skip_past_char (&p, '[') == SUCCESS)
    {
      expressionS exp;
      /* We got a scalar index.  */
    
      if (typeinfo.defined & NTA_HASINDEX)
        {
          as_bad (_("can't redefine the index of a scalar alias"));
          return 0;
        }
    
      my_get_expression (&exp, &p, GE_NO_PREFIX);
    
      if (exp.X_op != O_constant)
        {
          as_bad (_("scalar index must be constant"));
          return 0;
        }
      
      typeinfo.defined |= NTA_HASINDEX;
      typeinfo.index = exp.X_add_number;
    
      if (skip_past_char (&p, ']') == FAIL)
        {
          as_bad (_("expecting ]"));
          return 0;
        }
    }

  namelen = nameend - newname;
  namebuf = alloca (namelen + 1);
  strncpy (namebuf, newname, namelen);
  namebuf[namelen] = '\0';
  
  insert_neon_reg_alias (namebuf, basereg->number, basetype,
                         typeinfo.defined != 0 ? &typeinfo : NULL);
    
  /* Insert name in all uppercase.  */
  for (p = namebuf; *p; p++)
    *p = TOUPPER (*p);
  
  if (strncmp (namebuf, newname, namelen))
    insert_neon_reg_alias (namebuf, basereg->number, basetype,
                           typeinfo.defined != 0 ? &typeinfo : NULL);
  
  /* Insert name in all lowercase.  */
  for (p = namebuf; *p; p++)
    *p = TOLOWER (*p);
  
  if (strncmp (namebuf, newname, namelen))
    insert_neon_reg_alias (namebuf, basereg->number, basetype,
                           typeinfo.defined != 0 ? &typeinfo : NULL);
  
  return 1;
}