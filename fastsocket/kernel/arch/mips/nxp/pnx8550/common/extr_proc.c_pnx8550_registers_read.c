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
 int read_c0_cause () ; 
 int read_c0_compare () ; 
 int read_c0_compare2 () ; 
 int read_c0_compare3 () ; 
 int read_c0_config1 () ; 
 int read_c0_config2 () ; 
 int read_c0_config3 () ; 
 int read_c0_config7 () ; 
 int read_c0_count () ; 
 int read_c0_count2 () ; 
 int read_c0_count3 () ; 
 int read_c0_status () ; 
 scalar_t__ sprintf (char*,char*,int) ; 

__attribute__((used)) static int pnx8550_registers_read(char* page, char** start, off_t offset, int count, int* eof, void* data)
{
        int len = 0;

        if (offset==0) {
                len += sprintf(&page[len], "config1:   %#10.8x\n", read_c0_config1());
                len += sprintf(&page[len], "config2:   %#10.8x\n", read_c0_config2());
                len += sprintf(&page[len], "config3:   %#10.8x\n", read_c0_config3());
                len += sprintf(&page[len], "configPR:  %#10.8x\n", read_c0_config7());
                len += sprintf(&page[len], "status:    %#10.8x\n", read_c0_status());
                len += sprintf(&page[len], "cause:     %#10.8x\n", read_c0_cause());
                len += sprintf(&page[len], "count:     %#10.8x\n", read_c0_count());
                len += sprintf(&page[len], "count_2:   %#10.8x\n", read_c0_count2());
                len += sprintf(&page[len], "count_3:   %#10.8x\n", read_c0_count3());
                len += sprintf(&page[len], "compare:   %#10.8x\n", read_c0_compare());
                len += sprintf(&page[len], "compare_2: %#10.8x\n", read_c0_compare2());
                len += sprintf(&page[len], "compare_3: %#10.8x\n", read_c0_compare3());
        }

        return len;
}