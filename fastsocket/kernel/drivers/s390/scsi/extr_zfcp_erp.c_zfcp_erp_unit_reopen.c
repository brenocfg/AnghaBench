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
struct zfcp_unit {struct zfcp_port* port; } ;
struct zfcp_port {struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {int /*<<< orphan*/  erp_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  config_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  _zfcp_erp_unit_reopen (struct zfcp_unit*,int,char*,void*) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ zfcp_data ; 

void zfcp_erp_unit_reopen(struct zfcp_unit *unit, int clear, char *id,
			  void *ref)
{
	unsigned long flags;
	struct zfcp_port *port = unit->port;
	struct zfcp_adapter *adapter = port->adapter;

	read_lock_irqsave(&zfcp_data.config_lock, flags);
	write_lock(&adapter->erp_lock);
	_zfcp_erp_unit_reopen(unit, clear, id, ref);
	write_unlock(&adapter->erp_lock);
	read_unlock_irqrestore(&zfcp_data.config_lock, flags);
}