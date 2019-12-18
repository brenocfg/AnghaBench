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
struct sockaddr_atmsvc {int dummy; } ;
struct sockaddr_atmpvc {int dummy; } ;
struct atm_vcc {int /*<<< orphan*/  qos; } ;
typedef  enum atmsvc_msg_type { ____Placeholder_atmsvc_msg_type } atmsvc_msg_type ;

/* Variables and functions */
 int /*<<< orphan*/  sigd_enq2 (struct atm_vcc*,int,struct atm_vcc*,struct sockaddr_atmpvc const*,struct sockaddr_atmsvc const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void sigd_enq(struct atm_vcc *vcc,enum atmsvc_msg_type type,
    struct atm_vcc *listen_vcc,const struct sockaddr_atmpvc *pvc,
    const struct sockaddr_atmsvc *svc)
{
	sigd_enq2(vcc,type,listen_vcc,pvc,svc,vcc ? &vcc->qos : NULL,0);
	/* other ISP applications may use "reply" */
}