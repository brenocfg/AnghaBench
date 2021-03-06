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
struct zfcp_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  config_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_SET ; 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_ACCESS_BOXED ; 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__ zfcp_data ; 
 int /*<<< orphan*/  zfcp_erp_modify_port_status (struct zfcp_port*,char*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_erp_port_reopen (struct zfcp_port*,int /*<<< orphan*/ ,char*,void*) ; 

void zfcp_erp_port_boxed(struct zfcp_port *port, char *id, void *ref)
{
	unsigned long flags;

	read_lock_irqsave(&zfcp_data.config_lock, flags);
	zfcp_erp_modify_port_status(port, id, ref,
				    ZFCP_STATUS_COMMON_ACCESS_BOXED, ZFCP_SET);
	read_unlock_irqrestore(&zfcp_data.config_lock, flags);
	zfcp_erp_port_reopen(port, ZFCP_STATUS_COMMON_ERP_FAILED, id, ref);
}