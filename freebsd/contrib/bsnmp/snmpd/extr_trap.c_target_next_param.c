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
struct target_param {int dummy; } ;

/* Variables and functions */
 struct target_param* SLIST_NEXT (struct target_param*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tp ; 

struct target_param *
target_next_param(struct target_param *param)
{
	if (param == NULL)
		return (NULL);

	return (SLIST_NEXT(param, tp));
}