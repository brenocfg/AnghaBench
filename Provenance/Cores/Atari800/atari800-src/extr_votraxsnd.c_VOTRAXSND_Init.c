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
struct Votrax_interface {int num; int /*<<< orphan*/  BusyCallback; } ;
typedef  int /*<<< orphan*/  SWORD ;

/* Variables and functions */
 scalar_t__ Atari800_TV_PAL ; 
 scalar_t__ Atari800_tv_mode ; 
 void* FALSE ; 
 int /*<<< orphan*/  Log_print (char*,int) ; 
 void* PBI_XLD_v_enabled ; 
 scalar_t__ Util_malloc (int) ; 
 int VOICEBOX_BASEAUDF ; 
 void* VOICEBOX_enabled ; 
 void* VOTRAXSND_busy ; 
 int /*<<< orphan*/  VOTRAXSND_busy_callback_async ; 
 int VTRX_BLOCK_SIZE ; 
 scalar_t__ VTRX_RATE ; 
 int /*<<< orphan*/  Votrax_Start (void*) ; 
 int /*<<< orphan*/  Votrax_Stop () ; 
 int bit16 ; 
 int dsprate ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int num_pokeys ; 
 int ratio ; 
 int samples_per_frame ; 
 int /*<<< orphan*/ * temp_votrax_buffer ; 
 int /*<<< orphan*/ * votrax_buffer ; 
 scalar_t__ votrax_sync_samples ; 
 int /*<<< orphan*/  votraxsnd_enabled () ; 

void VOTRAXSND_Init(int playback_freq, int n_pokeys, int b16)
{
	static struct Votrax_interface vi;
	int temp_votrax_buffer_size;
	bit16 = b16;
	dsprate = playback_freq;
	num_pokeys = n_pokeys;
	if (!votraxsnd_enabled()) return;
	if (num_pokeys != 1 && num_pokeys != 2) {
		Log_print("VOTRAXSND_Init: cannot handle num_pokeys=%d", num_pokeys);
#ifdef PBI_XLD
		PBI_XLD_v_enabled = FALSE;
#endif
#ifdef VOICEBOX
		VOICEBOX_enabled = FALSE;
#endif
		return;
	}
	vi.num = 1;
	vi.BusyCallback = VOTRAXSND_busy_callback_async;
	Votrax_Stop();
	Votrax_Start((void *)&vi);
	samples_per_frame = dsprate/(Atari800_tv_mode == Atari800_TV_PAL ? 50 : 60);
	ratio = (double)VTRX_RATE/(double)dsprate;
#ifdef VOICEBOX
	temp_votrax_buffer_size = (int)(VTRX_BLOCK_SIZE*ratio*(VOICEBOX_BASEAUDF+1) + 10); /* +10 .. little extra? */
#else
	temp_votrax_buffer_size = (int)(VTRX_BLOCK_SIZE*ratio + 10); /* +10 .. little extra? */
#endif
	free(temp_votrax_buffer);
	temp_votrax_buffer = (SWORD *)Util_malloc(temp_votrax_buffer_size*sizeof(SWORD));
	free(votrax_buffer);
	votrax_buffer = (SWORD *)Util_malloc(VTRX_BLOCK_SIZE*sizeof(SWORD));

	VOTRAXSND_busy = FALSE;
	votrax_sync_samples = 0;
}