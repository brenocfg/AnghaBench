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
struct qeth_ipaddr {int proto; int /*<<< orphan*/  type; } ;
typedef  enum qeth_prot_versions { ____Placeholder_qeth_prot_versions } qeth_prot_versions ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  QETH_IP_TYPE_NORMAL ; 
 struct qeth_ipaddr* kzalloc (int,int /*<<< orphan*/ ) ; 

struct qeth_ipaddr *qeth_l3_get_addr_buffer(
				enum qeth_prot_versions prot)
{
	struct qeth_ipaddr *addr;

	addr = kzalloc(sizeof(struct qeth_ipaddr), GFP_ATOMIC);
	if (addr == NULL) {
		return NULL;
	}
	addr->type = QETH_IP_TYPE_NORMAL;
	addr->proto = prot;
	return addr;
}