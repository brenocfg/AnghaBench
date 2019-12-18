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
struct see_register_properties {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct see_register_properties*) ; 

__attribute__((used)) static void
hash_del_properties (void *p)
{
  struct see_register_properties *curr_prop = p;
  free (curr_prop);
}