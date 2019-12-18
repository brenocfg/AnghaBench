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
#define  ADB_PACKET 128 
 int /*<<< orphan*/  adb_input (unsigned char*,int,unsigned char) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void
cuda_input(unsigned char *buf, int nb)
{
    int i;

    switch (buf[0]) {
    case ADB_PACKET:
#ifdef CONFIG_XMON
	if (nb == 5 && buf[2] == 0x2c) {
	    extern int xmon_wants_key, xmon_adb_keycode;
	    if (xmon_wants_key) {
		xmon_adb_keycode = buf[3];
		return;
	    }
	}
#endif /* CONFIG_XMON */
#ifdef CONFIG_ADB
	adb_input(buf+2, nb-2, buf[1] & 0x40);
#endif /* CONFIG_ADB */
	break;

    default:
	printk("data from cuda (%d bytes):", nb);
	for (i = 0; i < nb; ++i)
	    printk(" %.2x", buf[i]);
	printk("\n");
    }
}