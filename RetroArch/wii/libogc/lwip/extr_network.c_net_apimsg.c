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
struct TYPE_2__ {struct api_msg* apimsg; } ;
struct net_msg {TYPE_1__ msg; int /*<<< orphan*/  type; } ;
struct api_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LWIP_ERROR (char*) ; 
 int /*<<< orphan*/  MEMP_API_MSG ; 
 int /*<<< orphan*/  MEMP_TCPIP_MSG ; 
 int /*<<< orphan*/  MQ_MSG_BLOCK ; 
 int /*<<< orphan*/  MQ_Send (int /*<<< orphan*/ ,struct net_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETMSG_API ; 
 int /*<<< orphan*/  TCPIP_DEBUG ; 
 int /*<<< orphan*/  memp_free (int /*<<< orphan*/ ,struct api_msg*) ; 
 struct net_msg* memp_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netthread_mbox ; 

__attribute__((used)) static void net_apimsg(struct api_msg *apimsg)
{
	struct net_msg *msg = memp_malloc(MEMP_TCPIP_MSG);

	LWIP_DEBUGF(TCPIP_DEBUG, ("net_apimsg: %p\n",apimsg));
	if(msg==NULL) {
		LWIP_ERROR(("net_apimsg: msg out of memory.\n"));
		memp_free(MEMP_API_MSG,apimsg);
		return;
	}

	msg->type = NETMSG_API;
	msg->msg.apimsg = apimsg;
	MQ_Send(netthread_mbox,msg,MQ_MSG_BLOCK);
}