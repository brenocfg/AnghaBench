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
typedef  int uint64_t ;
typedef  void* uint16_t ;
struct tm {int tm_isdst; void* tm_sec; void* tm_min; void* tm_hour; void* tm_year; void* tm_mon; void* tm_mday; } ;

/* Variables and functions */

__attribute__((used)) static void mz_zip_dosdate_to_raw_tm(uint64_t dos_date, struct tm *ptm)
{
    uint64_t date = (uint64_t)(dos_date >> 16);

    ptm->tm_mday  = (uint16_t)(date & 0x1f);
    ptm->tm_mon   = (uint16_t)(((date & 0x1E0) / 0x20) - 1);
    ptm->tm_year  = (uint16_t)(((date & 0x0FE00) / 0x0200) + 80);
    ptm->tm_hour  = (uint16_t)((dos_date & 0xF800) / 0x800);
    ptm->tm_min   = (uint16_t)((dos_date & 0x7E0) / 0x20);
    ptm->tm_sec   = (uint16_t)(2 * (dos_date & 0x1f));
    ptm->tm_isdst = -1;
}