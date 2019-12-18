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
typedef  int /*<<< orphan*/  u16 ;
struct sock {int dummy; } ;
struct ccid {TYPE_1__* ccid_ops; } ;
struct TYPE_2__ {int (* ccid_hc_rx_parse_options ) (struct sock*,unsigned char,unsigned char,int /*<<< orphan*/ ,unsigned char*) ;} ;

/* Variables and functions */
 int stub1 (struct sock*,unsigned char,unsigned char,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static inline int ccid_hc_rx_parse_options(struct ccid *ccid, struct sock *sk,
					   unsigned char option,
					   unsigned char len, u16 idx,
					   unsigned char* value)
{
	int rc = 0;
	if (ccid->ccid_ops->ccid_hc_rx_parse_options != NULL)
		rc = ccid->ccid_ops->ccid_hc_rx_parse_options(sk, option, len, idx, value);
	return rc;
}