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
struct TYPE_3__ {int /*<<< orphan*/  reg_val; } ;
struct TYPE_4__ {TYPE_1__ value; } ;
typedef  TYPE_2__ reg_entry ;
typedef  int /*<<< orphan*/  reg ;

/* Variables and functions */
 scalar_t__ hash_find (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nullregister ; 
 int /*<<< orphan*/  regp_hash ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static reg
get_register_pair (char *reg_name)
{
  const reg_entry *reg;
  char tmp_rp[16]="\0";

  /* Add '(' and ')' to the reg pair, if its not present.  */
  if (reg_name[0] != '(') 
    {
      tmp_rp[0] = '(';
      strcat (tmp_rp, reg_name);
      strcat (tmp_rp,")");
      reg = (const reg_entry *) hash_find (regp_hash, tmp_rp);
    }
  else
    reg = (const reg_entry *) hash_find (regp_hash, reg_name);

  if (reg != NULL)
    return reg->value.reg_val;

  return nullregister;
}