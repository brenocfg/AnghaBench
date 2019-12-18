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
struct se_lun {int /*<<< orphan*/  lun_shutdown_comp; } ;

/* Variables and functions */
 int /*<<< orphan*/  __transport_clear_lun_from_sessions (struct se_lun*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int transport_clear_lun_thread(void *p)
{
	struct se_lun *lun = p;

	__transport_clear_lun_from_sessions(lun);
	complete(&lun->lun_shutdown_comp);

	return 0;
}