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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct vacm_view {int /*<<< orphan*/  viewname; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 struct vacm_view* vacm_first_view () ; 
 struct vacm_view* vacm_next_view (struct vacm_view*) ; 

__attribute__((used)) static struct vacm_view *
vacm_get_view_by_name(u_char *octets, u_int len)
{
	struct vacm_view *view;

	for (view = vacm_first_view(); view != NULL; view = vacm_next_view(view))
		if (strlen(view->viewname) == len &&
		    memcmp(octets, view->viewname, len) == 0)
			return (view);

	return (NULL);
}