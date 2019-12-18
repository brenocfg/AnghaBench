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
struct sk_buff {scalar_t__ len; } ;
struct afs_call {int dummy; } ;

/* Variables and functions */
 int EBADMSG ; 
 int /*<<< orphan*/  _enter (char*,scalar_t__,int) ; 

__attribute__((used)) static int afs_deliver_fs_give_up_callbacks(struct afs_call *call,
					    struct sk_buff *skb, bool last)
{
	_enter(",{%u},%d", skb->len, last);

	if (skb->len > 0)
		return -EBADMSG; /* shouldn't be any reply data */
	return 0;
}