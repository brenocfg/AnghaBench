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
struct savestate_state {long pos; int /*<<< orphan*/  size; } ;

/* Variables and functions */
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 

int state_fseek(void *file, long offset, int whence)
{
	struct savestate_state *state = file;

	switch (whence) {
	case SEEK_SET:
		state->pos = offset;
		break;
	case SEEK_CUR:
		state->pos += offset;
		break;
	case SEEK_END:
		state->pos = state->size + offset;
		break;
	}
	return (int)state->pos;
}