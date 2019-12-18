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
struct gunzip_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fatal (char*,int,int) ; 
 int gunzip_partial (struct gunzip_state*,void*,int) ; 

void gunzip_exactly(struct gunzip_state *state, void *dst, int dstlen)
{
	int len;

	len  = gunzip_partial(state, dst, dstlen);
	if (len < dstlen)
		fatal("\n\rgunzip_exactly: ran out of data!"
				" Wanted %d, got %d.\n\r", dstlen, len);
}