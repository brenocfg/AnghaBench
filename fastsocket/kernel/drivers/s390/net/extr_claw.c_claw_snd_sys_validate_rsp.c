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
struct net_device {struct claw_privbk* ml_priv; } ;
struct clawctl {int /*<<< orphan*/  correlator; int /*<<< orphan*/  linkid; } ;
struct claw_privbk {struct claw_env* p_env; } ;
struct claw_env {int /*<<< orphan*/  adapter_name; int /*<<< orphan*/  host_name; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CLAW_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSTEM_VALIDATE_RESPONSE ; 
 int claw_send_control (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup ; 

__attribute__((used)) static int
claw_snd_sys_validate_rsp(struct net_device *dev,
	struct clawctl *p_ctl, __u32 return_code)
{
        struct claw_env *  p_env;
        struct claw_privbk *privptr;
        int    rc;

	CLAW_DBF_TEXT(2, setup, "chkresp");
	privptr = dev->ml_priv;
        p_env=privptr->p_env;
        rc=claw_send_control(dev, SYSTEM_VALIDATE_RESPONSE,
		p_ctl->linkid,
		p_ctl->correlator,
                return_code,
		p_env->host_name,
		p_env->adapter_name  );
        return rc;
}