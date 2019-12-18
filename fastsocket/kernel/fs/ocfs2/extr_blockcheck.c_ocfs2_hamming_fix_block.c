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

/* Variables and functions */
 int /*<<< orphan*/  ocfs2_hamming_fix (void*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 

void ocfs2_hamming_fix_block(void *data, unsigned int blocksize,
			     unsigned int fix)
{
	ocfs2_hamming_fix(data, blocksize * 8, 0, fix);
}