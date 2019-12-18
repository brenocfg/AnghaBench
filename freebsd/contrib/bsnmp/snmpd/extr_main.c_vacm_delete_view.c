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
struct vacm_view {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct vacm_view*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct vacm_view*) ; 
 int /*<<< orphan*/  vacm_view ; 
 int /*<<< orphan*/  vacm_viewlist ; 
 int /*<<< orphan*/  vvl ; 

int
vacm_delete_view(struct vacm_view *view)
{
	SLIST_REMOVE(&vacm_viewlist, view, vacm_view, vvl);
	free(view);

	return (0);
}