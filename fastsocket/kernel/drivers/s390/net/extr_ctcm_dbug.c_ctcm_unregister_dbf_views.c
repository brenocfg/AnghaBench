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
 int CTCM_DBF_INFOS ; 
 TYPE_1__* ctcm_dbf ; 
 int /*<<< orphan*/  debug_unregister (int /*<<< orphan*/ *) ; 

void ctcm_unregister_dbf_views(void)
{
	int x;
	for (x = 0; x < CTCM_DBF_INFOS; x++) {
		debug_unregister(ctcm_dbf[x].id);
		ctcm_dbf[x].id = NULL;
	}
}