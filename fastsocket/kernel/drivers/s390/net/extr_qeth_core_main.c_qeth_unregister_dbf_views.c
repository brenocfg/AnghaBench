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
struct TYPE_2__ {int /*<<< orphan*/ * id; } ;

/* Variables and functions */
 int QETH_DBF_INFOS ; 
 int /*<<< orphan*/  debug_unregister (int /*<<< orphan*/ *) ; 
 TYPE_1__* qeth_dbf ; 

__attribute__((used)) static void qeth_unregister_dbf_views(void)
{
	int x;
	for (x = 0; x < QETH_DBF_INFOS; x++) {
		debug_unregister(qeth_dbf[x].id);
		qeth_dbf[x].id = NULL;
	}
}