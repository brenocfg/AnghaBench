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
typedef  int /*<<< orphan*/  KXLDLoggingCallback ;

/* Variables and functions */
 int /*<<< orphan*/  s_logging_callback ; 

void 
kxld_set_logging_callback(KXLDLoggingCallback logging_callback)
{
    s_logging_callback = logging_callback;
}