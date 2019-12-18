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
typedef  scalar_t__ tid_t ;
typedef  int /*<<< orphan*/  alist_t ;

/* Variables and functions */
 int /*<<< orphan*/  alist_add (int /*<<< orphan*/ *,void*,void*) ; 
 int /*<<< orphan*/  alist_find (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debug (int,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
add_mapping(alist_t *ta, tid_t srcid, tid_t tgtid)
{
	debug(3, "Adding mapping %u <%x> => %u <%x>\n", srcid, srcid, tgtid, tgtid);

	assert(!alist_find(ta, (void *)(uintptr_t)srcid, NULL));
	assert(srcid != 0 && tgtid != 0);

	alist_add(ta, (void *)(uintptr_t)srcid, (void *)(uintptr_t)tgtid);
}