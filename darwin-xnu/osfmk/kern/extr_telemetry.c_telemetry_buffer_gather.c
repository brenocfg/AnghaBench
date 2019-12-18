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
typedef  scalar_t__ user_addr_t ;
typedef  scalar_t__ uint32_t ;
struct micro_snapshot_buffer {scalar_t__ buffer; scalar_t__ size; scalar_t__ current_position; scalar_t__ end_point; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  DBG_MACH_STACKSHOT ; 
 int /*<<< orphan*/  KDBG (int,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int KERN_NO_SPACE ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MICROSTACKSHOT_GATHER ; 
 scalar_t__ STACKSHOT_MICRO_SNAPSHOT_MAGIC ; 
 int /*<<< orphan*/  TELEMETRY_LOCK () ; 
 int /*<<< orphan*/  TELEMETRY_UNLOCK () ; 
 int /*<<< orphan*/  assert (int) ; 
 int copyout (void*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  log_telemetry_output (scalar_t__,scalar_t__,scalar_t__) ; 
 struct micro_snapshot_buffer telemetry_buffer ; 
 scalar_t__ telemetry_bytes_since_last_mark ; 

int telemetry_buffer_gather(user_addr_t buffer, uint32_t *length, boolean_t mark, struct micro_snapshot_buffer * current_buffer)
{
	int result = 0;
	uint32_t oldest_record_offset;

	KDBG(MACHDBG_CODE(DBG_MACH_STACKSHOT, MICROSTACKSHOT_GATHER) | DBG_FUNC_START,
			mark, telemetry_bytes_since_last_mark, 0,
			(&telemetry_buffer != current_buffer));

	TELEMETRY_LOCK();

	if (current_buffer->buffer == 0) {
		*length = 0;
		goto out;
	}

	if (*length < current_buffer->size) {
		result = KERN_NO_SPACE;
		goto out;
	}

	/*
	 * Copy the ring buffer out to userland in order sorted by time: least recent to most recent.
	 * First, we need to search forward from the cursor to find the oldest record in our buffer.
	 */
	oldest_record_offset = current_buffer->current_position;
	do {
		if (((oldest_record_offset + sizeof(uint32_t)) > current_buffer->size) ||
		    ((oldest_record_offset + sizeof(uint32_t)) > current_buffer->end_point)) {

			if (*(uint32_t *)(uintptr_t)(current_buffer->buffer) == 0) {
				/*
				 * There is no magic number at the start of the buffer, which means
				 * it's empty; nothing to see here yet.
				 */
				*length = 0;
				goto out;
			}
			/*
			 * We've looked through the end of the active buffer without finding a valid
			 * record; that means all valid records are in a single chunk, beginning at
			 * the very start of the buffer.
			 */

			oldest_record_offset = 0;
			assert(*(uint32_t *)(uintptr_t)(current_buffer->buffer) == STACKSHOT_MICRO_SNAPSHOT_MAGIC);
			break;
		}

		if (*(uint32_t *)(uintptr_t)(current_buffer->buffer + oldest_record_offset) == STACKSHOT_MICRO_SNAPSHOT_MAGIC)
			break;

		/*
		 * There are no alignment guarantees for micro-stackshot records, so we must search at each
		 * byte offset.
		 */
		oldest_record_offset++;
	} while (oldest_record_offset != current_buffer->current_position);

	/*
	 * If needed, copyout in two chunks: from the oldest record to the end of the buffer, and then
	 * from the beginning of the buffer up to the current position.
	 */
	if (oldest_record_offset != 0) {
#if TELEMETRY_DEBUG
		log_telemetry_output(current_buffer->buffer, oldest_record_offset,
		                     current_buffer->end_point - oldest_record_offset);
#endif
		if ((result = copyout((void *)(current_buffer->buffer + oldest_record_offset), buffer,
		    current_buffer->end_point - oldest_record_offset)) != 0) {
			*length = 0;
			goto out;
		}
		*length = current_buffer->end_point - oldest_record_offset;
	} else {
		*length = 0;
	}

#if TELEMETRY_DEBUG
	log_telemetry_output(current_buffer->buffer, 0, current_buffer->current_position);
#endif
	if ((result = copyout((void *)current_buffer->buffer, buffer + *length,
	    current_buffer->current_position)) != 0) {
		*length = 0;
		goto out;
	}
	*length += (uint32_t)current_buffer->current_position;

out:

	if (mark && (*length > 0)) {
		telemetry_bytes_since_last_mark = 0;
	}

	TELEMETRY_UNLOCK();

	KDBG(MACHDBG_CODE(DBG_MACH_STACKSHOT, MICROSTACKSHOT_GATHER) | DBG_FUNC_END,
			current_buffer->current_position, *length,
			current_buffer->end_point, (&telemetry_buffer != current_buffer));

	return (result);
}