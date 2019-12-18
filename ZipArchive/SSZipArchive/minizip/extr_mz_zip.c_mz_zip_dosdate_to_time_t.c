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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mktime (struct tm*) ; 
 int /*<<< orphan*/  mz_zip_dosdate_to_raw_tm (int /*<<< orphan*/ ,struct tm*) ; 

time_t mz_zip_dosdate_to_time_t(uint64_t dos_date)
{
    struct tm ptm;
    mz_zip_dosdate_to_raw_tm(dos_date, &ptm);
    return mktime(&ptm);
}