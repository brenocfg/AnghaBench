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
struct ttypes_filter {int /*<<< orphan*/  t; } ;

/* Variables and functions */
 int type_list_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ehspec_filter_eq (const void *pentry, const void *pdata)
{
  const struct ttypes_filter *entry = (const struct ttypes_filter *) pentry;
  const struct ttypes_filter *data = (const struct ttypes_filter *) pdata;

  return type_list_equal (entry->t, data->t);
}