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
 int /*<<< orphan*/  INI_PRINTK (char*) ; 

__attribute__((used)) static inline void NCR5380_all_init (void)
{
    static int done = 0;
    if (!done) {
	INI_PRINTK("scsi : NCR5380_all_init()\n");
	done = 1;
    }
}