#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  play_channels; int /*<<< orphan*/  play_sample_rate; int /*<<< orphan*/  play_sample_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFCHANNELS ; 
 int /*<<< orphan*/  DEFSAMPLERATE ; 
 int /*<<< orphan*/  DEFSAMPLESIZE ; 
 TYPE_1__ dev ; 

__attribute__((used)) static void set_default_play_audio_parameters(void)
{
	dev.play_sample_size = DEFSAMPLESIZE;
	dev.play_sample_rate = DEFSAMPLERATE;
	dev.play_channels = DEFCHANNELS;
}