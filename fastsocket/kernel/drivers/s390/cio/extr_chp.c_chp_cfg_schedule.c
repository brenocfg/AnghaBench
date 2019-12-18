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
struct chp_id {int /*<<< orphan*/  id; int /*<<< orphan*/  cssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_MSG_EVENT (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int cfg_busy ; 
 int /*<<< orphan*/  cfg_configure ; 
 int /*<<< orphan*/  cfg_deconfigure ; 
 int /*<<< orphan*/  cfg_lock ; 
 int /*<<< orphan*/  cfg_set_task (struct chp_id,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg_work ; 
 int /*<<< orphan*/  chp_wq ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void chp_cfg_schedule(struct chp_id chpid, int configure)
{
	CIO_MSG_EVENT(2, "chp_cfg_sched%x.%02x=%d\n", chpid.cssid, chpid.id,
		      configure);
	mutex_lock(&cfg_lock);
	cfg_set_task(chpid, configure ? cfg_configure : cfg_deconfigure);
	cfg_busy = 1;
	mutex_unlock(&cfg_lock);
	queue_work(chp_wq, &cfg_work);
}