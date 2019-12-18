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
struct net_device {int mtu; struct claw_privbk* ml_priv; } ;
struct claw_privbk {TYPE_1__* p_env; } ;
struct TYPE_2__ {int write_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAW_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static int
claw_change_mtu(struct net_device *dev, int new_mtu)
{
	struct claw_privbk *privptr = dev->ml_priv;
	int buff_size;
	CLAW_DBF_TEXT(4, trace, "setmtu");
	buff_size = privptr->p_env->write_size;
        if ((new_mtu < 60) || (new_mtu > buff_size)) {
                return -EINVAL;
        }
        dev->mtu = new_mtu;
        return 0;
}