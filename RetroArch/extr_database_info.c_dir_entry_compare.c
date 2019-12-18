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
struct string_list_elem {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int type_is_prioritized (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dir_entry_compare(const void *left, const void *right)
{
   const struct string_list_elem *le = (const struct string_list_elem*)left;
   const struct string_list_elem *re = (const struct string_list_elem*)right;
   bool                            l = type_is_prioritized(le->data);
   bool                            r = type_is_prioritized(re->data);

   return (int) r - (int) l;
}