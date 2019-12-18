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
struct snd_cs46xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_RQ_C1_DEST_MOD1024 ; 
 int /*<<< orphan*/  DMA_RQ_C1_DEST_MOD128 ; 
 int /*<<< orphan*/  DMA_RQ_C1_DEST_MOD16 ; 
 int /*<<< orphan*/  DMA_RQ_C1_DEST_MOD256 ; 
 int /*<<< orphan*/  DMA_RQ_C1_DEST_MOD32 ; 
 int /*<<< orphan*/  DMA_RQ_C1_DEST_MOD512 ; 
 int /*<<< orphan*/  DMA_RQ_C1_DEST_MOD64 ; 
 int /*<<< orphan*/  DMA_RQ_C1_DEST_SIZE_MASK ; 
 int EINVAL ; 
 int WRITEBACK_SCB_ADDR ; 
 int /*<<< orphan*/  snd_cs46xx_peek (struct snd_cs46xx*,int) ; 
 int /*<<< orphan*/  snd_cs46xx_poke (struct snd_cs46xx*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_printdd (char*,int) ; 

int cs46xx_dsp_pcm_ostream_set_period (struct snd_cs46xx * chip,
				       int period_size)
{
	u32 temp = snd_cs46xx_peek (chip,WRITEBACK_SCB_ADDR << 2);
	temp &= ~DMA_RQ_C1_DEST_SIZE_MASK;

	switch (period_size) {
	case 2048:
		temp |= DMA_RQ_C1_DEST_MOD1024;
		break;
	case 1024:
		temp |= DMA_RQ_C1_DEST_MOD512;
		break;
	case 512:
		temp |= DMA_RQ_C1_DEST_MOD256;
		break;
	case 256:
		temp |= DMA_RQ_C1_DEST_MOD128;
		break;
	case 128:
		temp |= DMA_RQ_C1_DEST_MOD64;
		break;
	case 64:
		temp |= DMA_RQ_C1_DEST_MOD32;
		break;		      
	case 32:
		temp |= DMA_RQ_C1_DEST_MOD16;
		break; 
	default:
		snd_printdd ("period size (%d) not supported by HW\n", period_size);
		return -EINVAL;
	}

	snd_cs46xx_poke (chip,WRITEBACK_SCB_ADDR << 2,temp);

	return 0;
}