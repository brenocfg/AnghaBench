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
typedef  int UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int*,int*,int) ; 

void GenerateEui64Address6(UCHAR *dst, UCHAR *mac)
{
	// Validate arguments
	if (dst == NULL || mac == NULL)
	{
		return;
	}

	Copy(dst, mac, 3);
	Copy(dst + 5, mac, 3);

	dst[3] = 0xff;
	dst[4] = 0xfe;
	dst[0] = ((~(dst[0] & 0x02)) & 0x02) | (dst[0] & 0xfd);
}