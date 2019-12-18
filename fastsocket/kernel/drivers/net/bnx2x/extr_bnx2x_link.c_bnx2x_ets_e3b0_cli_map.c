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
typedef  int u8 ;
struct link_params {int port; struct bnx2x* bp; } ;
struct bnx2x_ets_params {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CLIENT_IS_STRICT ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CLIENT_IS_SUBJECT2WFQ ; 
 int /*<<< orphan*/  NIG_REG_P1_TX_ARB_CLIENT_IS_STRICT ; 
 int /*<<< orphan*/  NIG_REG_P1_TX_ARB_CLIENT_IS_SUBJECT2WFQ ; 
 int /*<<< orphan*/  PBF_REG_ETS_ARB_CLIENT_IS_STRICT_P0 ; 
 int /*<<< orphan*/  PBF_REG_ETS_ARB_CLIENT_IS_STRICT_P1 ; 
 int /*<<< orphan*/  PBF_REG_ETS_ARB_CLIENT_IS_SUBJECT2WFQ_P0 ; 
 int /*<<< orphan*/  PBF_REG_ETS_ARB_CLIENT_IS_SUBJECT2WFQ_P1 ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static int bnx2x_ets_e3b0_cli_map(const struct link_params *params,
				  const struct bnx2x_ets_params *ets_params,
				  const u8 cos_sp_bitmap,
				  const u8 cos_bw_bitmap)
{
	struct bnx2x *bp = params->bp;
	const u8 port = params->port;
	const u8 nig_cli_sp_bitmap = 0x7 | (cos_sp_bitmap << 3);
	const u8 pbf_cli_sp_bitmap = cos_sp_bitmap;
	const u8 nig_cli_subject2wfq_bitmap = cos_bw_bitmap << 3;
	const u8 pbf_cli_subject2wfq_bitmap = cos_bw_bitmap;

	REG_WR(bp, (port) ? NIG_REG_P1_TX_ARB_CLIENT_IS_STRICT :
	       NIG_REG_P0_TX_ARB_CLIENT_IS_STRICT, nig_cli_sp_bitmap);

	REG_WR(bp, (port) ? PBF_REG_ETS_ARB_CLIENT_IS_STRICT_P1 :
	       PBF_REG_ETS_ARB_CLIENT_IS_STRICT_P0 , pbf_cli_sp_bitmap);

	REG_WR(bp, (port) ? NIG_REG_P1_TX_ARB_CLIENT_IS_SUBJECT2WFQ :
	       NIG_REG_P0_TX_ARB_CLIENT_IS_SUBJECT2WFQ,
	       nig_cli_subject2wfq_bitmap);

	REG_WR(bp, (port) ? PBF_REG_ETS_ARB_CLIENT_IS_SUBJECT2WFQ_P1 :
	       PBF_REG_ETS_ARB_CLIENT_IS_SUBJECT2WFQ_P0,
	       pbf_cli_subject2wfq_bitmap);

	return 0;
}