#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int reg_flags; int reg_type; } ;
typedef  TYPE_1__ reg_entry ;

/* Variables and functions */
 scalar_t__ CODE_64BIT ; 
 int Control ; 
 int CpuSledgehammer ; 
 int MAX_REG_NAME_SIZE ; 
 char REGISTER_PREFIX ; 
 int Reg64 ; 
 int RegRex ; 
 int RegRex64 ; 
 scalar_t__ allow_naked_reg ; 
 int cpu_arch_flags ; 
 scalar_t__ flag_code ; 
 TYPE_1__* hash_find (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ const* i386_regtab ; 
 scalar_t__* identifier_chars ; 
 scalar_t__ is_space_char (char) ; 
 int /*<<< orphan*/  know (TYPE_1__ const*) ; 
 int /*<<< orphan*/  reg_hash ; 
 char* register_chars ; 

__attribute__((used)) static const reg_entry *
parse_real_register (char *reg_string, char **end_op)
{
  char *s = reg_string;
  char *p;
  char reg_name_given[MAX_REG_NAME_SIZE + 1];
  const reg_entry *r;

  /* Skip possible REGISTER_PREFIX and possible whitespace.  */
  if (*s == REGISTER_PREFIX)
    ++s;

  if (is_space_char (*s))
    ++s;

  p = reg_name_given;
  while ((*p++ = register_chars[(unsigned char) *s]) != '\0')
    {
      if (p >= reg_name_given + MAX_REG_NAME_SIZE)
	return (const reg_entry *) NULL;
      s++;
    }

  /* For naked regs, make sure that we are not dealing with an identifier.
     This prevents confusing an identifier like `eax_var' with register
     `eax'.  */
  if (allow_naked_reg && identifier_chars[(unsigned char) *s])
    return (const reg_entry *) NULL;

  *end_op = s;

  r = (const reg_entry *) hash_find (reg_hash, reg_name_given);

  /* Handle floating point regs, allowing spaces in the (i) part.  */
  if (r == i386_regtab /* %st is first entry of table  */)
    {
      if (is_space_char (*s))
	++s;
      if (*s == '(')
	{
	  ++s;
	  if (is_space_char (*s))
	    ++s;
	  if (*s >= '0' && *s <= '7')
	    {
	      int fpr = *s - '0';
	      ++s;
	      if (is_space_char (*s))
		++s;
	      if (*s == ')')
		{
		  *end_op = s + 1;
		  r = hash_find (reg_hash, "st(0)");
		  know (r);
		  return r + fpr;
		}
	    }
	  /* We have "%st(" then garbage.  */
	  return (const reg_entry *) NULL;
	}
    }

  if (r != NULL
      && ((r->reg_flags & (RegRex64 | RegRex)) | (r->reg_type & Reg64)) != 0
      && (r->reg_type != Control || !(cpu_arch_flags & CpuSledgehammer))
      && flag_code != CODE_64BIT)
    return (const reg_entry *) NULL;

  return r;
}