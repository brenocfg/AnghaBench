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
typedef  int /*<<< orphan*/  u8 ;
struct iucv_path {int dummy; } ;
struct iucv_message {int flags; } ;

/* Variables and functions */
 int IUCV_IPRMDATA ; 
 int __iucv_message_receive (struct iucv_path*,struct iucv_message*,int /*<<< orphan*/ ,void*,size_t,size_t*) ; 
 int iucv_message_receive_iprmdata (struct iucv_path*,struct iucv_message*,int /*<<< orphan*/ ,void*,size_t,size_t*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 

int iucv_message_receive(struct iucv_path *path, struct iucv_message *msg,
			 u8 flags, void *buffer, size_t size, size_t *residual)
{
	int rc;

	if (msg->flags & IUCV_IPRMDATA)
		return iucv_message_receive_iprmdata(path, msg, flags,
						     buffer, size, residual);
	local_bh_disable();
	rc = __iucv_message_receive(path, msg, flags, buffer, size, residual);
	local_bh_enable();
	return rc;
}