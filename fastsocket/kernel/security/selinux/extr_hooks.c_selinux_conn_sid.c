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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ SECSID_NULL ; 
 int security_sid_mls_copy (scalar_t__,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static int selinux_conn_sid(u32 sk_sid, u32 skb_sid, u32 *conn_sid)
{
	int err = 0;

	if (skb_sid != SECSID_NULL)
		err = security_sid_mls_copy(sk_sid, skb_sid, conn_sid);
	else
		*conn_sid = sk_sid;

	return err;
}