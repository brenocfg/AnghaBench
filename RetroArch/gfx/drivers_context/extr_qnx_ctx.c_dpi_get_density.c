#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  screen_disp; } ;
typedef  TYPE_1__ qnx_ctx_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  SCREEN_PROPERTY_DPI ; 
 int min (int,int) ; 
 scalar_t__ screen_get_display_property_iv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int dpi_get_density(qnx_ctx_data_t *qnx)
{
    int screen_dpi[2];

    if(!qnx)
        return -1;

    if (screen_get_display_property_iv(qnx->screen_disp,
             SCREEN_PROPERTY_DPI, screen_dpi))
    {
       RARCH_ERR("screen_get_display_property_iv [SCREEN_PROPERTY_DPI] failed.\n");
       return -1;
    }

    return min(screen_dpi[0], screen_dpi[1]);
}