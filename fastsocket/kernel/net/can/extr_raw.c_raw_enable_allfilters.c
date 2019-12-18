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
struct raw_sock {int /*<<< orphan*/  count; int /*<<< orphan*/  filter; int /*<<< orphan*/  err_mask; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  raw_disable_filters (struct net_device*,struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int raw_enable_errfilter (struct net_device*,struct sock*,int /*<<< orphan*/ ) ; 
 int raw_enable_filters (struct net_device*,struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct raw_sock* raw_sk (struct sock*) ; 

__attribute__((used)) static int raw_enable_allfilters(struct net_device *dev, struct sock *sk)
{
	struct raw_sock *ro = raw_sk(sk);
	int err;

	err = raw_enable_filters(dev, sk, ro->filter, ro->count);
	if (!err) {
		err = raw_enable_errfilter(dev, sk, ro->err_mask);
		if (err)
			raw_disable_filters(dev, sk, ro->filter, ro->count);
	}

	return err;
}