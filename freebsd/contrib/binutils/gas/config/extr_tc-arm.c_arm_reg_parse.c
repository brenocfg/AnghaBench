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
struct reg_entry {int type; int number; TYPE_1__* neon; } ;
typedef  enum arm_reg_type { ____Placeholder_arm_reg_type } arm_reg_type ;
struct TYPE_2__ {int defined; } ;

/* Variables and functions */
 int FAIL ; 
 int NTA_HASINDEX ; 
 int arm_reg_alt_syntax (char**,char*,struct reg_entry*,int) ; 
 struct reg_entry* arm_reg_parse_multi (char**) ; 

__attribute__((used)) static int
arm_reg_parse (char **ccp, enum arm_reg_type type)
{
  char *start = *ccp;
  struct reg_entry *reg = arm_reg_parse_multi (ccp);
  int ret;

  /* Do not allow a scalar (reg+index) to parse as a register.  */
  if (reg && reg->neon && (reg->neon->defined & NTA_HASINDEX))
    return FAIL;

  if (reg && reg->type == type)
    return reg->number;

  if ((ret = arm_reg_alt_syntax (ccp, start, reg, type)) != FAIL)
    return ret;

  *ccp = start;
  return FAIL;
}