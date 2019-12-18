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
struct zfcp_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_SET ; 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int /*<<< orphan*/  zfcp_erp_modify_port_status (struct zfcp_port*,char*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void zfcp_erp_port_failed(struct zfcp_port *port, char *id, void *ref)
{
	zfcp_erp_modify_port_status(port, id, ref,
				    ZFCP_STATUS_COMMON_ERP_FAILED, ZFCP_SET);
}