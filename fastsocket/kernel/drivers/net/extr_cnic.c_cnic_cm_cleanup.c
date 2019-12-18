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
struct cnic_sock {scalar_t__ src_port; struct cnic_dev* dev; } ;
struct cnic_local {int /*<<< orphan*/  csk_port_tbl; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  cnic_free_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cnic_cm_cleanup(struct cnic_sock *csk)
{
	if (csk->src_port) {
		struct cnic_dev *dev = csk->dev;
		struct cnic_local *cp = dev->cnic_priv;

		cnic_free_id(&cp->csk_port_tbl, be16_to_cpu(csk->src_port));
		csk->src_port = 0;
	}
}