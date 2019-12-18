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
struct fc_els_spp {int spp_flags; } ;

/* Variables and functions */
 int FC_SPP_EST_IMG_PAIR ; 
 int FC_SPP_RESP_ACK ; 
 int FC_SPP_RESP_INVL ; 

__attribute__((used)) static int fc_rport_t0_prli(struct fc_rport_priv *rdata, u32 spp_len,
			    const struct fc_els_spp *rspp,
			    struct fc_els_spp *spp)
{
	if (rspp->spp_flags & FC_SPP_EST_IMG_PAIR)
		return FC_SPP_RESP_INVL;
	return FC_SPP_RESP_ACK;
}