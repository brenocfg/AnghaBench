#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  status; } ;
struct TYPE_4__ {TYPE_1__ ret_unlink; } ;
struct usbip_header {TYPE_2__ u; int /*<<< orphan*/  base; } ;
struct stub_unlink {int /*<<< orphan*/  status; int /*<<< orphan*/  seqnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBIP_RET_UNLINK ; 
 int /*<<< orphan*/  setup_base_pdu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_ret_unlink_pdu(struct usbip_header *rpdu,
		struct stub_unlink *unlink)
{
	setup_base_pdu(&rpdu->base, USBIP_RET_UNLINK, unlink->seqnum);

	rpdu->u.ret_unlink.status = unlink->status;
}