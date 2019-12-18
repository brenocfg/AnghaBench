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
struct zfcp_erp_action {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_STATUS_ERP_TIMEDOUT ; 
 int /*<<< orphan*/  zfcp_erp_notify (struct zfcp_erp_action*,int /*<<< orphan*/ ) ; 

void zfcp_erp_timeout_handler(unsigned long data)
{
	struct zfcp_erp_action *act = (struct zfcp_erp_action *) data;
	zfcp_erp_notify(act, ZFCP_STATUS_ERP_TIMEDOUT);
}