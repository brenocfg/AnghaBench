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
struct TYPE_4__ {int swap; int /*<<< orphan*/  sndrate; } ;
struct TYPE_3__ {int buffer_size; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRAMES_PER_SECOND ; 
 TYPE_2__ option ; 
 int /*<<< orphan*/  osd_play_streamed_sample_16 (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ snd ; 

void dos_update_audio(void)
{
  osd_play_streamed_sample_16(option.swap ^ 0, snd.buffer[0], snd.buffer_size * 2, option.sndrate, FRAMES_PER_SECOND, -100);
  osd_play_streamed_sample_16(option.swap ^ 1, snd.buffer[1], snd.buffer_size * 2, option.sndrate, FRAMES_PER_SECOND,  100);
}