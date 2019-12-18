#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  value; } ;
struct TYPE_4__ {int /*<<< orphan*/  range; int /*<<< orphan*/  value; } ;
struct TYPE_5__ {TYPE_3__ verdict; TYPE_1__ mode; } ;
struct ipq_peer_msg {TYPE_2__ msg; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IPQM_MODE 129 
#define  IPQM_VERDICT 128 
 int /*<<< orphan*/  NF_MAX_VERDICT ; 
 int ipq_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ipq_set_verdict (TYPE_3__*,unsigned int) ; 

__attribute__((used)) static int
ipq_receive_peer(struct ipq_peer_msg *pmsg,
		 unsigned char type, unsigned int len)
{
	int status = 0;

	if (len < sizeof(*pmsg))
		return -EINVAL;

	switch (type) {
	case IPQM_MODE:
		status = ipq_set_mode(pmsg->msg.mode.value,
				      pmsg->msg.mode.range);
		break;

	case IPQM_VERDICT:
		if (pmsg->msg.verdict.value > NF_MAX_VERDICT)
			status = -EINVAL;
		else
			status = ipq_set_verdict(&pmsg->msg.verdict,
						 len - sizeof(*pmsg));
			break;
	default:
		status = -EINVAL;
	}
	return status;
}