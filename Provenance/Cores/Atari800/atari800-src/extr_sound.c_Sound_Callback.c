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
typedef  int /*<<< orphan*/  UBYTE ;
struct TYPE_2__ {int channels; int sample_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  FillBuffer (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  Log_print (char*,int,unsigned int) ; 
 TYPE_1__ Sound_out ; 
 int /*<<< orphan*/  Util_time () ; 
 int /*<<< orphan*/  last_audio_write_time ; 
 int sync_read_pos ; 
 int sync_write_pos ; 

void Sound_Callback(UBYTE *buffer, unsigned int size)
{
#if DEBUG >= 2
		Log_print("Callback: fill %u, needed %u",
		          (sync_write_pos - sync_read_pos) / Sound_out.channels / Sound_out.sample_size,
		          size / Sound_out.channels / Sound_out.sample_size);
#endif
	FillBuffer(buffer, size);
#ifdef SYNCHRONIZED_SOUND
	last_audio_write_time = Util_time();
#endif /* SYNCHRONIZED_SOUND */
}