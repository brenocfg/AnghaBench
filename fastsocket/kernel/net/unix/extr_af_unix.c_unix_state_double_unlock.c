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
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  unix_state_unlock (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void unix_state_double_unlock(struct sock *sk1, struct sock *sk2)
{
	if (unlikely(sk1 == sk2) || !sk2) {
		unix_state_unlock(sk1);
		return;
	}
	unix_state_unlock(sk1);
	unix_state_unlock(sk2);
}