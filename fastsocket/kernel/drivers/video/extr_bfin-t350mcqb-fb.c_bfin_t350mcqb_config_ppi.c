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
struct bfin_t350mcqbfb_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ H_ACTPIX ; 
 int /*<<< orphan*/  H_START ; 
 int PPI_PACK_EN ; 
 int PPI_POLS_1 ; 
 int PPI_PORT_CFG_01 ; 
 int PPI_TX_MODE ; 
 int PPI_XFER_TYPE_11 ; 
 int /*<<< orphan*/  V_LINES ; 
 int /*<<< orphan*/  bfin_write_PPI_CONTROL (int) ; 
 int /*<<< orphan*/  bfin_write_PPI_COUNT (scalar_t__) ; 
 int /*<<< orphan*/  bfin_write_PPI_DELAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_PPI_FRAME (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bfin_t350mcqb_config_ppi(struct bfin_t350mcqbfb_info *fbi)
{
	bfin_write_PPI_DELAY(H_START);
	bfin_write_PPI_COUNT(H_ACTPIX-1);
	bfin_write_PPI_FRAME(V_LINES);

	bfin_write_PPI_CONTROL(PPI_TX_MODE |	   /* output mode , PORT_DIR */
				PPI_XFER_TYPE_11 | /* sync mode XFR_TYPE */
				PPI_PORT_CFG_01 |  /* two frame sync PORT_CFG */
				PPI_PACK_EN |	   /* packing enabled PACK_EN */
				PPI_POLS_1);	   /* faling edge syncs POLS */
}