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
struct beiscsi_hba {scalar_t__ ipv4_iface; int /*<<< orphan*/  shost; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
 int ENODEV ; 
 int /*<<< orphan*/  ISCSI_IFACE_TYPE_IPV4 ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  beiscsi_iscsi_transport ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ iscsi_create_iface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int beiscsi_create_ipv4_iface(struct beiscsi_hba *phba)
{
	if (phba->ipv4_iface)
		return 0;

	phba->ipv4_iface = iscsi_create_iface(phba->shost,
					      &beiscsi_iscsi_transport,
					      ISCSI_IFACE_TYPE_IPV4,
					      0, 0);
	if (!phba->ipv4_iface) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
			    "BS_%d : Could not "
			    "create default IPv4 address.\n");
		return -ENODEV;
	}

	return 0;
}