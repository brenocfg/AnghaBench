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
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_FORMAT_ERROR ; 
 int /*<<< orphan*/  MZ_OK ; 
 int /*<<< orphan*/  MZ_PARAM_ERROR ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mz_zip_dosdate_to_raw_tm (int /*<<< orphan*/ ,struct tm*) ; 
 scalar_t__ mz_zip_invalid_date (struct tm*) ; 

int32_t mz_zip_dosdate_to_tm(uint64_t dos_date, struct tm *ptm)
{
    if (ptm == NULL)
        return MZ_PARAM_ERROR;

    mz_zip_dosdate_to_raw_tm(dos_date, ptm);

    if (mz_zip_invalid_date(ptm))
    {
        /* Invalid date stored, so don't return it */
        memset(ptm, 0, sizeof(struct tm));
        return MZ_FORMAT_ERROR;
    }
    return MZ_OK;
}