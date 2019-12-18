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
struct TYPE_2__ {unsigned int channels; unsigned int sample_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  Log_print (char*,unsigned int,unsigned int) ; 
 int MAX_FRAME_SIZE ; 
 int /*<<< orphan*/  POKEYSND_Process (int /*<<< orphan*/ *,unsigned int) ; 
 TYPE_1__ Sound_out ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * sync_buffer ; 
 unsigned int sync_buffer_size ; 
 unsigned int sync_read_pos ; 
 unsigned int sync_write_pos ; 

__attribute__((used)) static void FillBuffer(UBYTE *buffer, unsigned int size)
{
#ifdef SYNCHRONIZED_SOUND
	unsigned int new_read_pos;
	static UBYTE last_frame[MAX_FRAME_SIZE];
	unsigned int bytes_per_frame = Sound_out.channels * Sound_out.sample_size;
	unsigned int to_write = sync_write_pos - sync_read_pos;

	if (to_write > 0) {
		if (to_write > size)
			to_write = size;

		new_read_pos = sync_read_pos + to_write;

		if (new_read_pos <= sync_buffer_size)
			/* no wrap */
			memcpy(buffer, sync_buffer + sync_read_pos, to_write);
		else {
			/* wraps */
			unsigned int first_part_size = sync_buffer_size - sync_read_pos;
			memcpy(buffer, sync_buffer + sync_read_pos, first_part_size);
			memcpy(buffer + first_part_size, sync_buffer, to_write - first_part_size);
		}

		sync_read_pos = new_read_pos;
		if (sync_read_pos > sync_buffer_size) {
			sync_read_pos -= sync_buffer_size;
			sync_write_pos -= sync_buffer_size;
		}
		/* Save the last frame as we may need it to fill underflow. */
		memcpy(last_frame, buffer + to_write - bytes_per_frame, bytes_per_frame);
	}


	/* Just repeat the last good frame if underflow. */
	if (to_write < size) {
#if DEBUG
		Log_print("Sound buffer underflow: fill %d, needed %d",
		          to_write/Sound_out.channels/Sound_out.sample_size,
		          size/Sound_out.channels/Sound_out.sample_size);
#endif
		do {
			memcpy(buffer + to_write, last_frame, bytes_per_frame);
			to_write += bytes_per_frame;
		} while (to_write < size);
	}
#else /* !SYNCHRONIZED_SOUND */
	POKEYSND_Process(buffer, size / Sound_out.sample_size);
#endif /* !SYNCHRONIZED_SOUND */
}