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
 int /*<<< orphan*/  RIO_DEBUG_PARAM ; 
 int /*<<< orphan*/  rio_dprintk (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void my_hd(void *ad, int len)
{
	int i, j, ch;
	unsigned char *addr = ad;

	for (i = 0; i < len; i += 16) {
		rio_dprintk(RIO_DEBUG_PARAM, "%08lx ", (unsigned long) addr + i);
		for (j = 0; j < 16; j++) {
			rio_dprintk(RIO_DEBUG_PARAM, "%02x %s", addr[j + i], (j == 7) ? " " : "");
		}
		for (j = 0; j < 16; j++) {
			ch = addr[j + i];
			rio_dprintk(RIO_DEBUG_PARAM, "%c", (ch < 0x20) ? '.' : ((ch > 0x7f) ? '.' : ch));
		}
		rio_dprintk(RIO_DEBUG_PARAM, "\n");
	}
}