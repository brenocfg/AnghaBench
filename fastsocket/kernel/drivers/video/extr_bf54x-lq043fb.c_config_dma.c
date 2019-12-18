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
struct bfin_bf54xfb_info {scalar_t__ fb_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_EPPI0 ; 
 int /*<<< orphan*/  DATA_SIZE_32 ; 
 int /*<<< orphan*/  DIMENSION_2D ; 
 int /*<<< orphan*/  DIR_READ ; 
 int DMA_BUS_SIZE ; 
 int /*<<< orphan*/  DMA_FLOW_AUTO ; 
 int /*<<< orphan*/  DMA_NOSYNC_KEEP_DMA_BUF ; 
 int /*<<< orphan*/  INTR_DISABLE ; 
 int LCD_BPP ; 
 int LCD_X_RES ; 
 int /*<<< orphan*/  LCD_Y_RES ; 
 int /*<<< orphan*/  set_bfin_dma_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_start_addr (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  set_dma_x_count (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_dma_x_modify (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_dma_y_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_y_modify (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int config_dma(struct bfin_bf54xfb_info *fbi)
{

	set_dma_config(CH_EPPI0,
		       set_bfin_dma_config(DIR_READ, DMA_FLOW_AUTO,
					   INTR_DISABLE, DIMENSION_2D,
					   DATA_SIZE_32,
					   DMA_NOSYNC_KEEP_DMA_BUF));
	set_dma_x_count(CH_EPPI0, (LCD_X_RES * LCD_BPP) / DMA_BUS_SIZE);
	set_dma_x_modify(CH_EPPI0, DMA_BUS_SIZE / 8);
	set_dma_y_count(CH_EPPI0, LCD_Y_RES);
	set_dma_y_modify(CH_EPPI0, DMA_BUS_SIZE / 8);
	set_dma_start_addr(CH_EPPI0, (unsigned long)fbi->fb_buffer);

	return 0;
}