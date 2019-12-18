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
struct audsrv_fmt_t {int bits; int freq; int channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  Log_print (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_VOLUME ; 
 int /*<<< orphan*/  audsrv_get_error_string () ; 
 scalar_t__ audsrv_init () ; 
 int /*<<< orphan*/  audsrv_set_format (struct audsrv_fmt_t*) ; 
 int /*<<< orphan*/  audsrv_set_volume (int /*<<< orphan*/ ) ; 

void Sound_Continue(void)
{
	if (audsrv_init() != 0)
		Log_print("failed to initialize audsrv: %s", audsrv_get_error_string());
	else {
		struct audsrv_fmt_t format;
		format.bits = 8;
		format.freq = 44100;
		format.channels = 1;
		audsrv_set_format(&format);
		audsrv_set_volume(MAX_VOLUME);
	}
}