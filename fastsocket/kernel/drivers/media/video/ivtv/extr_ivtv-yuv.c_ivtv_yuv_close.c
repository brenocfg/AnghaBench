#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ src_h; scalar_t__ src_w; } ;
struct TYPE_3__ {scalar_t__ src_h; scalar_t__ src_w; } ;
struct yuv_playback_info {int reg_2898; int reg_2834; int reg_2838; int reg_283c; int reg_2840; int reg_2844; int reg_2848; int reg_2854; int reg_285c; int reg_2864; int reg_2870; int reg_2874; int reg_2890; int reg_289c; int reg_2918; int reg_291c; int reg_2920; int reg_2924; int reg_2928; int reg_292c; int reg_2930; int reg_2934; int reg_2938; int reg_293c; int reg_2940; int reg_2944; int reg_2948; int reg_294c; int reg_2950; int reg_2954; int reg_2958; int reg_295c; int reg_2960; int reg_2964; int reg_2968; int reg_296c; int reg_2970; TYPE_2__ old_frame_info_args; TYPE_1__ old_frame_info; int /*<<< orphan*/  blanking_dmaptr; int /*<<< orphan*/ * blanking_ptr; int /*<<< orphan*/  next_fill_frame; int /*<<< orphan*/  next_dma_frame; scalar_t__ running; } ;
struct ivtv {int /*<<< orphan*/  i_flags; int /*<<< orphan*/  pdev; int /*<<< orphan*/  vsync_waitq; struct yuv_playback_info yuv_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_DEBUG_YUV (char*) ; 
 int /*<<< orphan*/  IVTV_F_I_DECODING_YUV ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtv_waitq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtv_yuv_filter (struct ivtv*,int,int,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg (int,int) ; 

void ivtv_yuv_close(struct ivtv *itv)
{
	struct yuv_playback_info *yi = &itv->yuv_info;
	int h_filter, v_filter_1, v_filter_2;

	IVTV_DEBUG_YUV("ivtv_yuv_close\n");
	ivtv_waitq(&itv->vsync_waitq);

	yi->running = 0;
	atomic_set(&yi->next_dma_frame, -1);
	atomic_set(&yi->next_fill_frame, 0);

	/* Reset registers we have changed so mpeg playback works */

	/* If we fully restore this register, the display may remain active.
	   Restore, but set one bit to blank the video. Firmware will always
	   clear this bit when needed, so not a problem. */
	write_reg(yi->reg_2898 | 0x01000000, 0x2898);

	write_reg(yi->reg_2834, 0x02834);
	write_reg(yi->reg_2838, 0x02838);
	write_reg(yi->reg_283c, 0x0283c);
	write_reg(yi->reg_2840, 0x02840);
	write_reg(yi->reg_2844, 0x02844);
	write_reg(yi->reg_2848, 0x02848);
	write_reg(yi->reg_2854, 0x02854);
	write_reg(yi->reg_285c, 0x0285c);
	write_reg(yi->reg_2864, 0x02864);
	write_reg(yi->reg_2870, 0x02870);
	write_reg(yi->reg_2874, 0x02874);
	write_reg(yi->reg_2890, 0x02890);
	write_reg(yi->reg_289c, 0x0289c);

	write_reg(yi->reg_2918, 0x02918);
	write_reg(yi->reg_291c, 0x0291c);
	write_reg(yi->reg_2920, 0x02920);
	write_reg(yi->reg_2924, 0x02924);
	write_reg(yi->reg_2928, 0x02928);
	write_reg(yi->reg_292c, 0x0292c);
	write_reg(yi->reg_2930, 0x02930);
	write_reg(yi->reg_2934, 0x02934);
	write_reg(yi->reg_2938, 0x02938);
	write_reg(yi->reg_293c, 0x0293c);
	write_reg(yi->reg_2940, 0x02940);
	write_reg(yi->reg_2944, 0x02944);
	write_reg(yi->reg_2948, 0x02948);
	write_reg(yi->reg_294c, 0x0294c);
	write_reg(yi->reg_2950, 0x02950);
	write_reg(yi->reg_2954, 0x02954);
	write_reg(yi->reg_2958, 0x02958);
	write_reg(yi->reg_295c, 0x0295c);
	write_reg(yi->reg_2960, 0x02960);
	write_reg(yi->reg_2964, 0x02964);
	write_reg(yi->reg_2968, 0x02968);
	write_reg(yi->reg_296c, 0x0296c);
	write_reg(yi->reg_2970, 0x02970);

	/* Prepare to restore filters */

	/* First the horizontal filter */
	if ((yi->reg_2834 & 0x0000FFFF) == (yi->reg_2834 >> 16)) {
		/* An exact size match uses filter 0 */
		h_filter = 0;
	} else {
		/* Figure out which filter to use */
		h_filter = ((yi->reg_2834 << 16) / (yi->reg_2834 >> 16)) >> 15;
		h_filter = (h_filter >> 1) + (h_filter & 1);
		/* Only an exact size match can use filter 0. */
		h_filter += !h_filter;
	}

	/* Now the vertical filter */
	if ((yi->reg_2918 & 0x0000FFFF) == (yi->reg_2918 >> 16)) {
		/* An exact size match uses filter 0/1 */
		v_filter_1 = 0;
		v_filter_2 = 1;
	} else {
		/* Figure out which filter to use */
		v_filter_1 = ((yi->reg_2918 << 16) / (yi->reg_2918 >> 16)) >> 15;
		v_filter_1 = (v_filter_1 >> 1) + (v_filter_1 & 1);
		/* Only an exact size match can use filter 0 */
		v_filter_1 += !v_filter_1;
		v_filter_2 = v_filter_1;
	}

	/* Now restore the filters */
	ivtv_yuv_filter(itv, h_filter, v_filter_1, v_filter_2);

	/* and clear a few registers */
	write_reg(0, 0x02814);
	write_reg(0, 0x0282c);
	write_reg(0, 0x02904);
	write_reg(0, 0x02910);

	/* Release the blanking buffer */
	if (yi->blanking_ptr) {
		kfree(yi->blanking_ptr);
		yi->blanking_ptr = NULL;
		pci_unmap_single(itv->pdev, yi->blanking_dmaptr, 720*16, PCI_DMA_TODEVICE);
	}

	/* Invalidate the old dimension information */
	yi->old_frame_info.src_w = 0;
	yi->old_frame_info.src_h = 0;
	yi->old_frame_info_args.src_w = 0;
	yi->old_frame_info_args.src_h = 0;

	/* All done. */
	clear_bit(IVTV_F_I_DECODING_YUV, &itv->i_flags);
}