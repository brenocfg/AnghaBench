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
struct sock {struct gprs_dev* sk_user_data; } ;
struct gprs_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  gprs_writeable (struct gprs_dev*) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gprs_write_space(struct sock *sk)
{
	struct gprs_dev *gp = sk->sk_user_data;

	if (netif_running(gp->dev))
		gprs_writeable(gp);
}