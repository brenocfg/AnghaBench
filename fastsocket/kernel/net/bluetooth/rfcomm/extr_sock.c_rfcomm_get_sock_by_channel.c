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
typedef  int /*<<< orphan*/  u8 ;
struct sock {int dummy; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct sock* __rfcomm_get_sock_by_channel (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ rfcomm_sk_list ; 

__attribute__((used)) static inline struct sock *rfcomm_get_sock_by_channel(int state, u8 channel, bdaddr_t *src)
{
	struct sock *s;
	read_lock(&rfcomm_sk_list.lock);
	s = __rfcomm_get_sock_by_channel(state, channel, src);
	if (s) bh_lock_sock(s);
	read_unlock(&rfcomm_sk_list.lock);
	return s;
}