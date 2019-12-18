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
struct TYPE_2__ {unsigned long data; scalar_t__ expires; int /*<<< orphan*/  function; } ;
struct zfcp_fsf_req {TYPE_1__ timer; scalar_t__ erp_action; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  zfcp_erp_timeout_handler ; 

__attribute__((used)) static void zfcp_fsf_start_erp_timer(struct zfcp_fsf_req *fsf_req)
{
	BUG_ON(!fsf_req->erp_action);
	fsf_req->timer.function = zfcp_erp_timeout_handler;
	fsf_req->timer.data = (unsigned long) fsf_req->erp_action;
	fsf_req->timer.expires = jiffies + 30 * HZ;
	add_timer(&fsf_req->timer);
}