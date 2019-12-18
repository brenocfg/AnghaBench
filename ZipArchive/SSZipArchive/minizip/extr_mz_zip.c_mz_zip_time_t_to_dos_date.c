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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mz_zip_time_t_to_tm (int /*<<< orphan*/ ,struct tm*) ; 
 int /*<<< orphan*/  mz_zip_tm_to_dosdate (struct tm const*) ; 

uint32_t mz_zip_time_t_to_dos_date(time_t unix_time)
{
    struct tm ptm;
    mz_zip_time_t_to_tm(unix_time, &ptm);
    return mz_zip_tm_to_dosdate((const struct tm *)&ptm);
}