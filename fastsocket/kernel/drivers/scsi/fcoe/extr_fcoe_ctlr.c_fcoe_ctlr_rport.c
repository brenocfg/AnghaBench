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
struct fcoe_rport {int dummy; } ;
struct fc_rport_priv {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct fcoe_rport *fcoe_ctlr_rport(struct fc_rport_priv *rdata)
{
	return (struct fcoe_rport *)(rdata + 1);
}