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
struct asm_cond {int value; } ;
struct TYPE_2__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int FAIL ; 
 scalar_t__ ISALPHA (char) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  arm_cond_hsh ; 
 struct asm_cond* hash_find_n (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__ inst ; 

__attribute__((used)) static int
parse_cond (char **str)
{
  char *p, *q;
  const struct asm_cond *c;

  p = q = *str;
  while (ISALPHA (*q))
    q++;

  c = hash_find_n (arm_cond_hsh, p, q - p);
  if (!c)
    {
      inst.error = _("condition required");
      return FAIL;
    }

  *str = q;
  return c->value;
}