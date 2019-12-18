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
struct zfcp_dbf {struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {int /*<<< orphan*/  erp_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  zfcp_dbf_rec_thread (char*,struct zfcp_dbf*) ; 

void zfcp_dbf_rec_thread_lock(char *id2, struct zfcp_dbf *dbf)
{
	struct zfcp_adapter *adapter = dbf->adapter;
	unsigned long flags;

	read_lock_irqsave(&adapter->erp_lock, flags);
	zfcp_dbf_rec_thread(id2, dbf);
	read_unlock_irqrestore(&adapter->erp_lock, flags);
}