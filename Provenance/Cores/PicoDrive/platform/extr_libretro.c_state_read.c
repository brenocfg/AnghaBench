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
struct savestate_state {scalar_t__ pos; scalar_t__ size; size_t load_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  lprintf (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void*,size_t,size_t) ; 

size_t state_read(void *p, size_t size, size_t nmemb, void *file)
{
	struct savestate_state *state = file;
	size_t bsize = size * nmemb;

	if (state->pos + bsize > state->size) {
		lprintf("savestate error: %u/%u\n",
			state->pos + bsize, state->size);
		bsize = state->size - state->pos;
		if ((int)bsize <= 0)
			return 0;
	}

	memcpy(p, state->load_buf + state->pos, bsize);
	state->pos += bsize;
	return bsize;
}