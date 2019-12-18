#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* Test; int /*<<< orphan*/  PSM; } ;
struct TYPE_5__ {scalar_t__ ZTE; } ;

/* Variables and functions */
 int* Colours_table ; 
 int /*<<< orphan*/  DMA_CHANNEL_GIF ; 
 int /*<<< orphan*/  D_CTRL_MFD_OFF ; 
 int /*<<< orphan*/  D_CTRL_RCYC_8 ; 
 int /*<<< orphan*/  D_CTRL_RELE_ON ; 
 int /*<<< orphan*/  D_CTRL_STD_OFF ; 
 int /*<<< orphan*/  D_CTRL_STS_UNSPEC ; 
 int FALSE ; 
 int /*<<< orphan*/  GS_MODE_NTSC ; 
 int /*<<< orphan*/  GS_PSM_CT32 ; 
 int /*<<< orphan*/  PAD_PORT ; 
 int /*<<< orphan*/  PAD_SLOT ; 
 int /*<<< orphan*/  Sound_Initialise (int*,char**) ; 
 int TRUE ; 
 int* clut ; 
 int /*<<< orphan*/  dmaKit_chan_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaKit_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* gsGlobal ; 
 TYPE_2__* gsKit_init_global (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsKit_init_screen (TYPE_2__*) ; 
 int /*<<< orphan*/  init_scr () ; 
 int /*<<< orphan*/  padBuf ; 
 int /*<<< orphan*/  padInit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  padPortOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_initialize () ; 

int PLATFORM_Initialise(int *argc, char *argv[])
{
	// Swap Red and Blue components
	int i;
	for (i = 0; i < 256; i++) {
		int c = Colours_table[i];
//		clut[i] = (c >> 16) + (c & 0xff00) + ((c & 0xff) << 16);
		// swap bits 3 and 4 to workaround a bug in gsKit
		clut[(i ^ i * 2) & 16 ? i ^ 24 : i] = (c >> 16) + (c & 0xff00) + ((c & 0xff) << 16);
	}
	// Clear debug from screen
	init_scr();
	// Initialize graphics
	gsGlobal = gsKit_init_global(GS_MODE_NTSC);
	dmaKit_init(D_CTRL_RELE_ON, D_CTRL_MFD_OFF, D_CTRL_STS_UNSPEC,
	            D_CTRL_STD_OFF, D_CTRL_RCYC_8);
	dmaKit_chan_init(DMA_CHANNEL_GIF);
	gsGlobal->PSM = GS_PSM_CT32;
	gsGlobal->Test->ZTE = 0;
	gsKit_init_screen(gsGlobal);
	// Init joypad
	padInit(0);
	padPortOpen(PAD_PORT, PAD_SLOT, padBuf);
#ifdef USE_TIMERS
	timer_initialize();
#endif
#ifdef SOUND
	if (!Sound_Initialise(argc, argv))
		return FALSE;
#endif

	return TRUE;
}