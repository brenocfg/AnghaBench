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
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct target_param*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct target_param*) ; 
 int /*<<< orphan*/  target_param ; 
 int /*<<< orphan*/  target_paramlist ; 
 int /*<<< orphan*/  tp ; 

int
target_delete_param(struct target_param *param)
{
	SLIST_REMOVE(&target_paramlist, param, target_param, tp);
	free(param);

	return (0);
}