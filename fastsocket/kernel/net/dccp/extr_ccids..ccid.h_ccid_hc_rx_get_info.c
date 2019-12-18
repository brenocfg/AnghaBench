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
struct tcp_info {int dummy; } ;
struct sock {int dummy; } ;
struct ccid {TYPE_1__* ccid_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ccid_hc_rx_get_info ) (struct sock*,struct tcp_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct sock*,struct tcp_info*) ; 

__attribute__((used)) static inline void ccid_hc_rx_get_info(struct ccid *ccid, struct sock *sk,
				       struct tcp_info *info)
{
	if (ccid->ccid_ops->ccid_hc_rx_get_info != NULL)
		ccid->ccid_ops->ccid_hc_rx_get_info(sk, info);
}