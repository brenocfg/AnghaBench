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
struct sock {int dummy; } ;
struct ccid {TYPE_1__* ccid_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ccid_hc_tx_packet_sent ) (struct sock*,int,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct sock*,int,unsigned int) ; 

__attribute__((used)) static inline void ccid_hc_tx_packet_sent(struct ccid *ccid, struct sock *sk,
					  int more, unsigned int len)
{
	if (ccid->ccid_ops->ccid_hc_tx_packet_sent != NULL)
		ccid->ccid_ops->ccid_hc_tx_packet_sent(sk, more, len);
}