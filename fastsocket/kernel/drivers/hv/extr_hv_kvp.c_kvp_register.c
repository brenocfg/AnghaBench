#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int operation; } ;
struct TYPE_5__ {char* version; } ;
struct TYPE_6__ {TYPE_1__ kvp_register; } ;
struct hv_kvp_msg {TYPE_4__ kvp_hdr; TYPE_2__ body; } ;
struct TYPE_7__ {int /*<<< orphan*/  val; int /*<<< orphan*/  idx; } ;
struct cn_msg {int len; TYPE_3__ id; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN_KVP_IDX ; 
 int /*<<< orphan*/  CN_KVP_VAL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HV_DRV_VERSION ; 
 int /*<<< orphan*/  cn_netlink_send (struct cn_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cn_msg*) ; 
 struct cn_msg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kvp_register(int reg_value)
{

	struct cn_msg *msg;
	struct hv_kvp_msg *kvp_msg;
	char *version;

	msg = kzalloc(sizeof(*msg) + sizeof(struct hv_kvp_msg), GFP_ATOMIC);

	if (msg) {
		kvp_msg = (struct hv_kvp_msg *)msg->data;
		version = kvp_msg->body.kvp_register.version;
		msg->id.idx =  CN_KVP_IDX;
		msg->id.val = CN_KVP_VAL;

		kvp_msg->kvp_hdr.operation = reg_value;
		strcpy(version, HV_DRV_VERSION);
		msg->len = sizeof(struct hv_kvp_msg);
		cn_netlink_send(msg, 0, GFP_ATOMIC);
		kfree(msg);
	}
}