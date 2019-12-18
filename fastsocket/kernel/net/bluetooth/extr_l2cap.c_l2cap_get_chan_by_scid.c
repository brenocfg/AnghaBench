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
typedef  int /*<<< orphan*/  u16 ;
struct sock {int dummy; } ;
struct l2cap_chan_list {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct sock* __l2cap_get_chan_by_scid (struct l2cap_chan_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct sock *l2cap_get_chan_by_scid(struct l2cap_chan_list *l, u16 cid)
{
	struct sock *s;
	read_lock(&l->lock);
	s = __l2cap_get_chan_by_scid(l, cid);
	if (s)
		bh_lock_sock(s);
	read_unlock(&l->lock);
	return s;
}