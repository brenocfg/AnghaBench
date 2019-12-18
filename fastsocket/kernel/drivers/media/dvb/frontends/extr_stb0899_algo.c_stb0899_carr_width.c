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
struct stb0899_internal {int srate; int rolloff; } ;
struct stb0899_state {struct stb0899_internal internal; } ;

/* Variables and functions */

long stb0899_carr_width(struct stb0899_state *state)
{
	struct stb0899_internal *internal = &state->internal;

	return (internal->srate + (internal->srate * internal->rolloff) / 100);
}