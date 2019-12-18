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
typedef  scalar_t__ u8 ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct iucv_path {int dummy; } ;
struct iucv_message {int dummy; } ;
struct TYPE_2__ {int (* message_send ) (struct iucv_path*,struct iucv_message*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IUCV_IPRMDATA ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,void*,scalar_t__) ; 
 TYPE_1__* pr_iucv ; 
 int stub1 (struct iucv_path*,struct iucv_message*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int iucv_send_iprm(struct iucv_path *path, struct iucv_message *msg,
			  struct sk_buff *skb)
{
	u8 prmdata[8];

	memcpy(prmdata, (void *) skb->data, skb->len);
	prmdata[7] = 0xff - (u8) skb->len;
	return pr_iucv->message_send(path, msg, IUCV_IPRMDATA, 0,
				 (void *) prmdata, 8);
}