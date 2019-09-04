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
struct TYPE_3__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ CACAContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 char** caca_get_display_driver_list () ; 

__attribute__((used)) static void list_drivers(CACAContext *c)
{
    const char *const *drivers = caca_get_display_driver_list();
    int i;

    av_log(c->ctx, AV_LOG_INFO, "Available drivers:\n");
    for (i = 0; drivers[i]; i += 2)
        av_log(c->ctx, AV_LOG_INFO, "%s: %s\n", drivers[i], drivers[i + 1]);
}