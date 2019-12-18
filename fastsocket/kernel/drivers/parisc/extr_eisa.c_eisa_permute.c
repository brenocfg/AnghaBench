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

__attribute__((used)) static inline unsigned long eisa_permute(unsigned short port)
{
	if (port & 0x300) {
		return 0xfc000000 | ((port & 0xfc00) >> 6)
			| ((port & 0x3f8) << 9) | (port & 7);
	} else {
		return 0xfc000000 | port;
	}
}