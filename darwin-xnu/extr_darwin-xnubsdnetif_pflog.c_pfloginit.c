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

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int PFLOGIFS_MAX ; 
 int /*<<< orphan*/  if_clone_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pflog_cloner ; 
 int /*<<< orphan*/  pflogif_list ; 
 int /*<<< orphan*/ ** pflogifs ; 

void
pfloginit(void)
{
	int i;

	LIST_INIT(&pflogif_list);
	for (i = 0; i < PFLOGIFS_MAX; i++)
		pflogifs[i] = NULL;

	(void) if_clone_attach(&pflog_cloner);
}