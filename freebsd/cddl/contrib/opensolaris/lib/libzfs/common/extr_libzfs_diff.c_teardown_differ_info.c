#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cleanupfd; int /*<<< orphan*/  tomnt; int /*<<< orphan*/  tmpsnap; int /*<<< orphan*/  tosnap; int /*<<< orphan*/  frommnt; int /*<<< orphan*/  fromsnap; int /*<<< orphan*/  dsmnt; int /*<<< orphan*/  ds; } ;
typedef  TYPE_1__ differ_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
teardown_differ_info(differ_info_t *di)
{
	free(di->ds);
	free(di->dsmnt);
	free(di->fromsnap);
	free(di->frommnt);
	free(di->tosnap);
	free(di->tmpsnap);
	free(di->tomnt);
	(void) close(di->cleanupfd);
}