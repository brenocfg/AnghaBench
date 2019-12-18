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
struct qmi_msg {int dummy; } ;
struct qmi_ctxt {int /*<<< orphan*/  dns2; int /*<<< orphan*/  dns1; int /*<<< orphan*/  gateway; int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 unsigned int qmi_get_tlv (struct qmi_msg*,int,int,unsigned char*) ; 
 int /*<<< orphan*/  swapaddr (unsigned char*,int /*<<< orphan*/ ) ; 
 unsigned char* zero ; 

__attribute__((used)) static void qmi_read_runtime_profile(struct qmi_ctxt *ctxt, struct qmi_msg *msg)
{
	unsigned char tmp[4];
	unsigned r;

	r = qmi_get_tlv(msg, 0x1e, 4, tmp);
	swapaddr(r ? zero : tmp, ctxt->addr);
	r = qmi_get_tlv(msg, 0x21, 4, tmp);
	swapaddr(r ? zero : tmp, ctxt->mask);
	r = qmi_get_tlv(msg, 0x20, 4, tmp);
	swapaddr(r ? zero : tmp, ctxt->gateway);
	r = qmi_get_tlv(msg, 0x15, 4, tmp);
	swapaddr(r ? zero : tmp, ctxt->dns1);
	r = qmi_get_tlv(msg, 0x16, 4, tmp);
	swapaddr(r ? zero : tmp, ctxt->dns2);
}