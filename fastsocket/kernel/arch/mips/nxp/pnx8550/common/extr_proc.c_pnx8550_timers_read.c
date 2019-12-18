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
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int read_c0_compare () ; 
 int read_c0_compare2 () ; 
 int read_c0_compare3 () ; 
 int read_c0_config7 () ; 
 int read_c0_count () ; 
 int read_c0_count2 () ; 
 int read_c0_count3 () ; 
 scalar_t__ sprintf (char*,char*,...) ; 

__attribute__((used)) static int pnx8550_timers_read(char* page, char** start, off_t offset, int count, int* eof, void* data)
{
        int len = 0;
	int configPR = read_c0_config7();

        if (offset==0) {
		len += sprintf(&page[len], "Timer:       count,  compare, tc, status\n");
                len += sprintf(&page[len], "    1: %11i, %8i,  %1i, %s\n",
			       read_c0_count(), read_c0_compare(),
			      (configPR>>6)&0x1, ((configPR>>3)&0x1)? "off":"on");
                len += sprintf(&page[len], "    2: %11i, %8i,  %1i, %s\n",
			       read_c0_count2(), read_c0_compare2(),
			      (configPR>>7)&0x1, ((configPR>>4)&0x1)? "off":"on");
                len += sprintf(&page[len], "    3: %11i, %8i,  %1i, %s\n",
			       read_c0_count3(), read_c0_compare3(),
			      (configPR>>8)&0x1, ((configPR>>5)&0x1)? "off":"on");
        }

        return len;
}