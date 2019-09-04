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
typedef  int /*<<< orphan*/  ver ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  section_header_t ;
typedef  int /*<<< orphan*/  image_header_t ;

/* Variables and functions */
 scalar_t__ const APP_START_OFFSET ; 
 scalar_t__ SPIRead (scalar_t__ const,scalar_t__*,int) ; 
 int /*<<< orphan*/  ets_printf (char const*,scalar_t__) ; 

int print_version(const uint32_t flash_addr)
{
    uint32_t ver;
    if (SPIRead(flash_addr + APP_START_OFFSET + sizeof(image_header_t) + sizeof(section_header_t), &ver, sizeof(ver))) {
        return 1;
    }
    const char* __attribute__ ((aligned (4))) fmtt = "v%08x\n\0\0";
    uint32_t fmt[2];
    fmt[0] = ((uint32_t*) fmtt)[0];
    fmt[1] = ((uint32_t*) fmtt)[1];
    ets_printf((const char*) fmt, ver);
    return 0;
}