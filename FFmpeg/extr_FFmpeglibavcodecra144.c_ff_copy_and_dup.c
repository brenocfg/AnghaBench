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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int BLOCKSIZE ; 
 int BUFFERSIZE ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

void ff_copy_and_dup(int16_t *target, const int16_t *source, int offset)
{
    source += BUFFERSIZE - offset;

    memcpy(target, source, FFMIN(BLOCKSIZE, offset)*sizeof(*target));
    if (offset < BLOCKSIZE)
        memcpy(target + offset, source, (BLOCKSIZE - offset)*sizeof(*target));
}