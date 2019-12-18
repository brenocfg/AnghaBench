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
struct savestate_state {size_t pos; } ;

/* Variables and functions */

size_t state_skip(void *p, size_t size, size_t nmemb, void *file)
{
	struct savestate_state *state = file;
	size_t bsize = size * nmemb;

	state->pos += bsize;
	return bsize;
}