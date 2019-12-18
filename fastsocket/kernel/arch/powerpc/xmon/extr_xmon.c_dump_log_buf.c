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
 int CONFIG_LOG_BUF_SHIFT ; 
 int /*<<< orphan*/  __delay (int) ; 
 int /*<<< orphan*/  bus_error_jmp ; 
 int catch_memory_errors ; 
 unsigned long kallsyms_lookup_name (char*) ; 
 int /*<<< orphan*/  mread (unsigned long,unsigned char*,unsigned long const) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 unsigned long const strlen (unsigned char*) ; 
 int /*<<< orphan*/  sync () ; 

void
dump_log_buf(void)
{
        const unsigned long size = 128;
        unsigned long end, addr;
        unsigned char buf[size + 1];

        addr = 0;
        buf[size] = '\0';

        if (setjmp(bus_error_jmp) != 0) {
                printf("Unable to lookup symbol __log_buf!\n");
                return;
        }

        catch_memory_errors = 1;
        sync();
        addr = kallsyms_lookup_name("__log_buf");

        if (! addr)
                printf("Symbol __log_buf not found!\n");
        else {
                end = addr + (1 << CONFIG_LOG_BUF_SHIFT);
                while (addr < end) {
                        if (! mread(addr, buf, size)) {
                                printf("Can't read memory at address 0x%lx\n", addr);
                                break;
                        }

                        printf("%s", buf);

                        if (strlen(buf) < size)
                                break;

                        addr += size;
                }
        }

        sync();
        /* wait a little while to see if we get a machine check */
        __delay(200);
        catch_memory_errors = 0;
}