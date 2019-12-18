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
struct itbl_entry {char* name; } ;
typedef  int /*<<< orphan*/  e_type ;
typedef  int /*<<< orphan*/  e_processor ;

/* Variables and functions */
 struct itbl_entry* find_entry_byval (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

char *
itbl_get_name (e_processor processor, e_type type, unsigned long val)
{
  struct itbl_entry *r;
  /* type depends on instruction passed */
  r = find_entry_byval (processor, type, val, 0);
  if (r)
    return r->name;
  else
    return 0;			/* error; invalid operand */
}