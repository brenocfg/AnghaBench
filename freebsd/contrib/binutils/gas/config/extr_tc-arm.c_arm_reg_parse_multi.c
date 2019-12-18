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
struct reg_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ ISALPHA (char) ; 
 scalar_t__ ISDIGIT (char) ; 
 char OPTIONAL_REGISTER_PREFIX ; 
 char REGISTER_PREFIX ; 
 int /*<<< orphan*/  arm_reg_hsh ; 
 scalar_t__ hash_find_n (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  is_name_beginner (char) ; 

__attribute__((used)) static struct reg_entry *
arm_reg_parse_multi (char **ccp)
{
  char *start = *ccp;
  char *p;
  struct reg_entry *reg;

#ifdef REGISTER_PREFIX
  if (*start != REGISTER_PREFIX)
    return NULL;
  start++;
#endif
#ifdef OPTIONAL_REGISTER_PREFIX
  if (*start == OPTIONAL_REGISTER_PREFIX)
    start++;
#endif

  p = start;
  if (!ISALPHA (*p) || !is_name_beginner (*p))
    return NULL;

  do
    p++;
  while (ISALPHA (*p) || ISDIGIT (*p) || *p == '_');

  reg = (struct reg_entry *) hash_find_n (arm_reg_hsh, start, p - start);

  if (!reg)
    return NULL;

  *ccp = p;
  return reg;
}