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
typedef  uintptr_t tid_t ;
typedef  int /*<<< orphan*/  alist_t ;

/* Variables and functions */
 scalar_t__ alist_find (int /*<<< orphan*/ *,void*,void**) ; 

__attribute__((used)) static tid_t
get_mapping(alist_t *ta, int srcid)
{
	void *ltgtid;

	if (alist_find(ta, (void *)(uintptr_t)srcid, (void **)&ltgtid))
		return ((uintptr_t)ltgtid);
	else
		return (0);
}