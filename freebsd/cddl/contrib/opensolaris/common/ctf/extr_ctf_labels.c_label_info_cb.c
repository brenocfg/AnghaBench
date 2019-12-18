#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * lca_info; int /*<<< orphan*/  lca_name; } ;
typedef  TYPE_1__ linfo_cb_arg_t ;
typedef  int /*<<< orphan*/  ctf_lblinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
label_info_cb(const char *lname, const ctf_lblinfo_t *linfo, void *arg)
{
	/*
	 * If lname matches the label we are looking for, copy the
	 * lblinfo_t struct for the caller.
	 */
	if (strcmp(lname, ((linfo_cb_arg_t *)arg)->lca_name) == 0) {
		/*
		 * Allow caller not to allocate storage to test if label exists
		 */
		if (((linfo_cb_arg_t *)arg)->lca_info != NULL)
			bcopy(linfo, ((linfo_cb_arg_t *)arg)->lca_info,
			    sizeof (ctf_lblinfo_t));
		return (1); /* Indicate we found a match */
	}

	return (0);
}