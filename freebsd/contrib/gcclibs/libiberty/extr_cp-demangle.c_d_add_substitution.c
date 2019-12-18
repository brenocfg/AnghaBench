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
struct demangle_component {int dummy; } ;
struct d_info {size_t next_sub; size_t num_subs; struct demangle_component** subs; } ;

/* Variables and functions */

__attribute__((used)) static int
d_add_substitution (struct d_info *di, struct demangle_component *dc)
{
  if (dc == NULL)
    return 0;
  if (di->next_sub >= di->num_subs)
    return 0;
  di->subs[di->next_sub] = dc;
  ++di->next_sub;
  return 1;
}