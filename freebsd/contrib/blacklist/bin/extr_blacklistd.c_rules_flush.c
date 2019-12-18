#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct conf {int dummy; } ;
struct TYPE_4__ {size_t cs_n; int /*<<< orphan*/ * cs_c; } ;
struct TYPE_3__ {size_t cs_n; int /*<<< orphan*/ * cs_c; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct conf**) ; 
 TYPE_2__ lconf ; 
 TYPE_1__ rconf ; 
 int /*<<< orphan*/  run_flush (struct conf*) ; 
 int /*<<< orphan*/  uniqueadd (struct conf***,size_t*,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rules_flush(void)
{
	struct conf **list;
	size_t nlist, mlist;

	list = NULL;
	mlist = nlist = 0;
	for (size_t i = 0; i < rconf.cs_n; i++)
		uniqueadd(&list, &nlist, &mlist, &rconf.cs_c[i]);
	for (size_t i = 0; i < lconf.cs_n; i++)
		uniqueadd(&list, &nlist, &mlist, &lconf.cs_c[i]);

	for (size_t i = 0; i < nlist; i++)
		run_flush(list[i]);
	free(list);
}