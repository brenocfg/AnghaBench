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

__attribute__((used)) static inline int is_PKCS11_padded(unsigned char *buffer, int length)
{
	int i;
	if ((buffer[0] != 0x00) || (buffer[1] != 0x01))
		return 0;
	for (i = 2; i < length; i++)
		if (buffer[i] != 0xFF)
			break;
	if (i < 10 || i == length)
		return 0;
	if (buffer[i] != 0x00)
		return 0;
	return 1;
}