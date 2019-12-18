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
typedef  int /*<<< orphan*/  u32 ;
struct fc_rport_priv {int dummy; } ;
struct fc_els_spp {int dummy; } ;

/* Variables and functions */
 int FC_SPP_RESP_INVL ; 

__attribute__((used)) static int fc_lport_els_prli(struct fc_rport_priv *rdata, u32 spp_len,
			     const struct fc_els_spp *spp_in,
			     struct fc_els_spp *spp_out)
{
	return FC_SPP_RESP_INVL;
}