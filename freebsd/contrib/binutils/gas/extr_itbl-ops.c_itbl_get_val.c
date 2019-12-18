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
struct itbl_entry {unsigned long value; } ;
typedef  int /*<<< orphan*/  e_type ;
typedef  int /*<<< orphan*/  e_processor ;

/* Variables and functions */
 struct itbl_entry* find_entry_byname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int
itbl_get_val (e_processor processor, e_type type, char *name,
	      unsigned long *pval)
{
  struct itbl_entry *r;
  /* type depends on instruction passed */
  r = find_entry_byname (processor, type, name);
  if (r == NULL)
    return 0;
  *pval = r->value;
  return 1;
}