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

/* Variables and functions */
 int /*<<< orphan*/  av_log_set_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_warnings ; 
 scalar_t__ num_warnings ; 

__attribute__((used)) static void init_count_warnings(void)
{
    av_log_set_callback(count_warnings);
    num_warnings = 0;
}