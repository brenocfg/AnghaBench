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
typedef  int /*<<< orphan*/  hb_filter_param_t ;

/* Variables and functions */
 int /*<<< orphan*/ * deinterlace_presets ; 
 int /*<<< orphan*/  hb_qsv_available () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void hb_param_configure_qsv(void)
{
#if HB_PROJECT_FEATURE_QSV
    if (!hb_qsv_available())
    {
        memset(&deinterlace_presets[4], 0, sizeof(hb_filter_param_t));
    }
#endif
}