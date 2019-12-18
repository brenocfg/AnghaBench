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
struct net_device {struct claw_privbk* ml_priv; } ;
struct clawctl {int /*<<< orphan*/  linkid; } ;
struct claw_privbk {int system_validate_comp; TYPE_1__* p_env; int /*<<< orphan*/  ctl_bk; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_2__ {scalar_t__ packing; int /*<<< orphan*/  api_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAW_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CONNECTION_REQUEST ; 
 int /*<<< orphan*/  HOST_APPL_NAME ; 
 scalar_t__ PACKING_ASK ; 
 scalar_t__ PACK_SEND ; 
 int /*<<< orphan*/  WS_APPL_NAME_IP_NAME ; 
 int /*<<< orphan*/  WS_APPL_NAME_PACKED ; 
 int claw_send_control (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup ; 

__attribute__((used)) static int
claw_snd_conn_req(struct net_device *dev, __u8 link)
{
        int                rc;
	struct claw_privbk *privptr = dev->ml_priv;
        struct clawctl 	   *p_ctl;

	CLAW_DBF_TEXT(2, setup, "snd_conn");
	rc = 1;
        p_ctl=(struct clawctl *)&privptr->ctl_bk;
	p_ctl->linkid = link;
        if ( privptr->system_validate_comp==0x00 ) {
                return rc;
        }
	if (privptr->p_env->packing == PACKING_ASK )
		rc=claw_send_control(dev, CONNECTION_REQUEST,0,0,0,
        		WS_APPL_NAME_PACKED, WS_APPL_NAME_PACKED);
	if (privptr->p_env->packing == PACK_SEND)  {
		rc=claw_send_control(dev, CONNECTION_REQUEST,0,0,0,
        		WS_APPL_NAME_IP_NAME, WS_APPL_NAME_IP_NAME);
	}
	if (privptr->p_env->packing == 0)
        	rc=claw_send_control(dev, CONNECTION_REQUEST,0,0,0,
       			HOST_APPL_NAME, privptr->p_env->api_type);
        return rc;

}