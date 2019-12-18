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
struct reg_entry {int number; int /*<<< orphan*/  type; } ;
typedef  enum arm_reg_type { ____Placeholder_arm_reg_type } arm_reg_type ;

/* Variables and functions */
 int FAIL ; 
 int /*<<< orphan*/  REG_TYPE_CN ; 
#define  REG_TYPE_CP 133 
#define  REG_TYPE_MMXWC 132 
 int /*<<< orphan*/  REG_TYPE_MMXWCG ; 
#define  REG_TYPE_MVD 131 
#define  REG_TYPE_MVDX 130 
#define  REG_TYPE_MVF 129 
#define  REG_TYPE_MVFX 128 
 unsigned long strtoul (char*,char**,int) ; 

__attribute__((used)) static int
arm_reg_alt_syntax (char **ccp, char *start, struct reg_entry *reg,
                    enum arm_reg_type type)
{
  /* Alternative syntaxes are accepted for a few register classes.  */
  switch (type)
    {
    case REG_TYPE_MVF:
    case REG_TYPE_MVD:
    case REG_TYPE_MVFX:
    case REG_TYPE_MVDX:
      /* Generic coprocessor register names are allowed for these.  */
      if (reg && reg->type == REG_TYPE_CN)
	return reg->number;
      break;

    case REG_TYPE_CP:
      /* For backward compatibility, a bare number is valid here.  */
      {
	unsigned long processor = strtoul (start, ccp, 10);
	if (*ccp != start && processor <= 15)
	  return processor;
      }

    case REG_TYPE_MMXWC:
      /* WC includes WCG.  ??? I'm not sure this is true for all
	 instructions that take WC registers.  */
      if (reg && reg->type == REG_TYPE_MMXWCG)
	return reg->number;
      break;

    default:
      break;
    }

  return FAIL;
}