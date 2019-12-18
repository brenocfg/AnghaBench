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
struct sock {size_t sk_family; } ;

/* Variables and functions */
 int /*<<< orphan*/ * af_family_key_strings ; 
 scalar_t__ af_family_keys ; 
 int /*<<< orphan*/ * af_family_slock_key_strings ; 
 scalar_t__ af_family_slock_keys ; 
 int /*<<< orphan*/  sock_lock_init_class_and_name (struct sock*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void sock_lock_init(struct sock *sk)
{
	sock_lock_init_class_and_name(sk,
			af_family_slock_key_strings[sk->sk_family],
			af_family_slock_keys + sk->sk_family,
			af_family_key_strings[sk->sk_family],
			af_family_keys + sk->sk_family);
}