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
struct bfin_t350mcqbfb_info {scalar_t__ fb_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_PPI ; 
 int /*<<< orphan*/  DATA_SIZE_16 ; 
 int /*<<< orphan*/  DIMENSION_2D ; 
 int /*<<< orphan*/  DIR_READ ; 
 int DMA_BUS_SIZE ; 
 int /*<<< orphan*/  DMA_FLOW_AUTO ; 
 int /*<<< orphan*/  DMA_NOSYNC_KEEP_DMA_BUF ; 
 int /*<<< orphan*/  INTR_DISABLE ; 
 int LCD_BPP ; 
 int LCD_X_RES ; 
 int /*<<< orphan*/  V_LINES ; 
 int /*<<< orphan*/  set_bfin_dma_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_start_addr (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  set_dma_x_count (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_dma_x_modify (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_dma_y_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_y_modify (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bfin_t350mcqb_config_dma(struct bfin_t350mcqbfb_info *fbi)
{

	set_dma_config(CH_PPI,
		       set_bfin_dma_config(DIR_READ, DMA_FLOW_AUTO,
					   INTR_DISABLE, DIMENSION_2D,
					   DATA_SIZE_16,
					   DMA_NOSYNC_KEEP_DMA_BUF));
	set_dma_x_count(CH_PPI, (LCD_X_RES * LCD_BPP) / DMA_BUS_SIZE);
	set_dma_x_modify(CH_PPI, DMA_BUS_SIZE / 8);
	set_dma_y_count(CH_PPI, V_LINES);

	set_dma_y_modify(CH_PPI, DMA_BUS_SIZE / 8);
	set_dma_start_addr(CH_PPI, (unsigned long)fbi->fb_buffer);

}