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
struct TYPE_2__ {scalar_t__ workspace; } ;
struct gunzip_state {TYPE_1__ s; } ;

/* Variables and functions */
 int gunzip_partial (struct gunzip_state*,void*,int) ; 
 int /*<<< orphan*/  zlib_inflateEnd (TYPE_1__*) ; 

int gunzip_finish(struct gunzip_state *state, void *dst, int dstlen)
{
	int len;

	len = gunzip_partial(state, dst, dstlen);

	if (state->s.workspace) {
		zlib_inflateEnd(&state->s);
	}

	return len;
}