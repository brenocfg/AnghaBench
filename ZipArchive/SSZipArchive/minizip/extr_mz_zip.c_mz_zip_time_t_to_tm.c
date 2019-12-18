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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_INTERNAL_ERROR ; 
 int /*<<< orphan*/  MZ_OK ; 
 int /*<<< orphan*/  MZ_PARAM_ERROR ; 
 int /*<<< orphan*/ * localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  memcpy (struct tm*,struct tm*,int) ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 

int32_t mz_zip_time_t_to_tm(time_t unix_time, struct tm *ptm)
{
    struct tm ltm;
    if (ptm == NULL)
        return MZ_PARAM_ERROR;
    if (localtime_r(&unix_time, &ltm) == NULL)  /* Returns a 1900-based year */
    {
        /* Invalid date stored, so don't return it */
        memset(ptm, 0, sizeof(struct tm));
        return MZ_INTERNAL_ERROR;
    }
    memcpy(ptm, &ltm, sizeof(struct tm));
    return MZ_OK;
}