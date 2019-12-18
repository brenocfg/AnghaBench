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
typedef  int /*<<< orphan*/  DTOVERLAY_LOGGING_FUNC ;

/* Variables and functions */
 int /*<<< orphan*/ * dtoverlay_logging_func ; 

void dtoverlay_set_logging_func(DTOVERLAY_LOGGING_FUNC *func)
{
    dtoverlay_logging_func = func;
}