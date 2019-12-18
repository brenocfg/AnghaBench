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
typedef  int /*<<< orphan*/  UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  dsp_fd ; 
 int write (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

void PLATFORM_SoundWrite(UBYTE const *buffer, unsigned int size)
{
	int wsize = write(dsp_fd, buffer, size);
	if (wsize < size) {
		/* TODO: handle problem */
	}
}