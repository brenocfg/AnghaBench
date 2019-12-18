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
 int mp3_find_sync_word (unsigned char*,int) ; 
 int* mpeg1_l3_bitrates ; 

__attribute__((used)) static int try_get_bitrate(unsigned char *buf, int buf_size)
{
	int offs1, offs = 0;
	int ret;

	while (1)
	{
		offs1 = mp3_find_sync_word(buf + offs, buf_size - offs);
		if (offs1 < 0)
			return -2;
		offs += offs1;
		if (buf_size - offs < 4)
			return -3;

		// printf("trying header %08x\n", *(int *)(buf + offs));

		ret = mpeg1_l3_bitrates[buf[offs + 2] >> 4];
		if (ret > 0)
			return ret;
	}

	return -2;
}