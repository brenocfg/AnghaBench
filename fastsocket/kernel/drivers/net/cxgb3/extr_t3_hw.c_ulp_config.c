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
struct tp_params {unsigned int chan_rx_size; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_ULPRX_TDDP_TAGMASK ; 
 int /*<<< orphan*/  ISCSI ; 
 int /*<<< orphan*/  PBL ; 
 int /*<<< orphan*/  RQ ; 
 int /*<<< orphan*/  STAG ; 
 int /*<<< orphan*/  TDDP ; 
 int /*<<< orphan*/  TPT ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ulp_region (struct adapter*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  ulptx_region (struct adapter*,int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static void ulp_config(struct adapter *adap, const struct tp_params *p)
{
	unsigned int m = p->chan_rx_size;

	ulp_region(adap, ISCSI, m, p->chan_rx_size / 8);
	ulp_region(adap, TDDP, m, p->chan_rx_size / 8);
	ulptx_region(adap, TPT, m, p->chan_rx_size / 4);
	ulp_region(adap, STAG, m, p->chan_rx_size / 4);
	ulp_region(adap, RQ, m, p->chan_rx_size / 4);
	ulptx_region(adap, PBL, m, p->chan_rx_size / 4);
	ulp_region(adap, PBL, m, p->chan_rx_size / 4);
	t3_write_reg(adap, A_ULPRX_TDDP_TAGMASK, 0xffffffff);
}