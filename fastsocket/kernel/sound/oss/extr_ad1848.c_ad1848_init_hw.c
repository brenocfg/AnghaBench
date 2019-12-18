#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ model; int audio_flags; } ;
typedef  TYPE_1__ ad1848_info ;

/* Variables and functions */
 int DMA_DUPLEX ; 
 scalar_t__ MD_1845 ; 
 scalar_t__ MD_1845_SSCAPE ; 
 scalar_t__ MD_1848 ; 
 scalar_t__ MD_4236 ; 
 scalar_t__ MD_IWAVE ; 
 int /*<<< orphan*/  ad1848_mixer_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  ad_enter_MCE (TYPE_1__*) ; 
 int /*<<< orphan*/  ad_leave_MCE (TYPE_1__*) ; 
 int /*<<< orphan*/  ad_mute (TYPE_1__*) ; 
 int ad_read (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ad_unmute (TYPE_1__*) ; 
 int /*<<< orphan*/  ad_write (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  io_Status (TYPE_1__*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ soundpro ; 

__attribute__((used)) static void ad1848_init_hw(ad1848_info * devc)
{
	int i;
	int *init_values;

	/*
	 * Initial values for the indirect registers of CS4248/AD1848.
	 */
	static int      init_values_a[] =
	{
		0xa8, 0xa8, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00,
		0x00, 0x0c, 0x02, 0x00, 0x8a, 0x01, 0x00, 0x00,

	/* Positions 16 to 31 just for CS4231/2 and ad1845 */
		0x80, 0x00, 0x10, 0x10, 0x00, 0x00, 0x1f, 0x40,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};

	static int      init_values_b[] =
	{
		/* 
		   Values for the newer chips
		   Some of the register initialization values were changed. In
		   order to get rid of the click that preceded PCM playback,
		   calibration was disabled on the 10th byte. On that same byte,
		   dual DMA was enabled; on the 11th byte, ADC dithering was
		   enabled, since that is theoretically desirable; on the 13th
		   byte, Mode 3 was selected, to enable access to extended
		   registers.
		 */
		0xa8, 0xa8, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00,
		0x00, 0x00, 0x06, 0x00, 0xe0, 0x01, 0x00, 0x00,
 		0x80, 0x00, 0x10, 0x10, 0x00, 0x00, 0x1f, 0x40,
 		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};

	/*
	 *	Select initialisation data
	 */
	 
	init_values = init_values_a;
	if(devc->model >= MD_4236)
		init_values = init_values_b;

	for (i = 0; i < 16; i++)
		ad_write(devc, i, init_values[i]);


	ad_mute(devc);		/* Initialize some variables */
	ad_unmute(devc);	/* Leave it unmuted now */

	if (devc->model > MD_1848)
	{
		if (devc->model == MD_1845_SSCAPE)
			ad_write(devc, 12, ad_read(devc, 12) | 0x50);
		else 
			ad_write(devc, 12, ad_read(devc, 12) | 0x40);		/* Mode2 = enabled */

		if (devc->model == MD_IWAVE)
			ad_write(devc, 12, 0x6c);	/* Select codec mode 3 */

		if (devc->model != MD_1845_SSCAPE)
			for (i = 16; i < 32; i++)
				ad_write(devc, i, init_values[i]);

		if (devc->model == MD_IWAVE)
			ad_write(devc, 16, 0x30);	/* Playback and capture counters enabled */
	}
	if (devc->model > MD_1848)
	{
		if (devc->audio_flags & DMA_DUPLEX)
			ad_write(devc, 9, ad_read(devc, 9) & ~0x04);	/* Dual DMA mode */
		else
			ad_write(devc, 9, ad_read(devc, 9) | 0x04);	/* Single DMA mode */

		if (devc->model == MD_1845 || devc->model == MD_1845_SSCAPE)
			ad_write(devc, 27, ad_read(devc, 27) | 0x08);		/* Alternate freq select enabled */

		if (devc->model == MD_IWAVE)
		{		/* Some magic Interwave specific initialization */
			ad_write(devc, 12, 0x6c);	/* Select codec mode 3 */
			ad_write(devc, 16, 0x30);	/* Playback and capture counters enabled */
			ad_write(devc, 17, 0xc2);	/* Alternate feature enable */
		}
	}
	else
	{
		  devc->audio_flags &= ~DMA_DUPLEX;
		  ad_write(devc, 9, ad_read(devc, 9) | 0x04);	/* Single DMA mode */
		  if (soundpro)
			  ad_write(devc, 12, ad_read(devc, 12) | 0x40);	/* Mode2 = enabled */
	}

	outb((0), io_Status(devc));	/* Clear pending interrupts */

	/*
	 * Toggle the MCE bit. It completes the initialization phase.
	 */

	ad_enter_MCE(devc);	/* In case the bit was off */
	ad_leave_MCE(devc);

	ad1848_mixer_reset(devc);
}