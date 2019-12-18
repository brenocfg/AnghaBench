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
struct type_info {int dummy; } ;
struct gcov_iterator {size_t type; struct type_info* type_info; } ;

/* Variables and functions */

__attribute__((used)) static struct type_info *get_type(struct gcov_iterator *iter)
{
	return &iter->type_info[iter->type];
}