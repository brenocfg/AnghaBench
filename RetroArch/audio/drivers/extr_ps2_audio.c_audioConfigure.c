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
struct audsrv_fmt_t {unsigned int freq; int /*<<< orphan*/  channels; int /*<<< orphan*/  bits; } ;
typedef  int /*<<< orphan*/  ps2_audio_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_BITS ; 
 int /*<<< orphan*/  AUDIO_CHANNELS ; 
 int /*<<< orphan*/  MAX_VOLUME ; 
 char* audsrv_get_error_string () ; 
 int audsrv_set_format (struct audsrv_fmt_t*) ; 
 int /*<<< orphan*/  audsrv_set_volume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void audioConfigure(ps2_audio_t *ps2, unsigned rate)
{
   int err;
   struct audsrv_fmt_t format;

   format.bits = AUDIO_BITS;
   format.freq = rate;
   format.channels = AUDIO_CHANNELS;

   err = audsrv_set_format(&format);

   if (err)
   {
      printf("set format returned %d\n", err);
      printf("audsrv returned error string: %s\n", audsrv_get_error_string());
   }

   audsrv_set_volume(MAX_VOLUME);
}