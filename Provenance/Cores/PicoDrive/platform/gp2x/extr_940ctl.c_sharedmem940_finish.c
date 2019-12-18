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
 int MP3_SIZE_MAX ; 
 int /*<<< orphan*/ * mp3_mem ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * shared_ctl ; 
 int /*<<< orphan*/ * shared_data ; 
 int /*<<< orphan*/ * shared_mem ; 

void sharedmem940_finish(void)
{
	munmap(shared_mem, 0x210000);
	munmap(mp3_mem, MP3_SIZE_MAX);
	shared_mem = mp3_mem = NULL;
	shared_data = NULL;
	shared_ctl = NULL;
}