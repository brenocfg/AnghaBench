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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int AV_LOG_WARNING ; 
 int /*<<< orphan*/  num_warnings ; 

__attribute__((used)) static void count_warnings(void *avcl, int level, const char *fmt, va_list vl)
{
    if (level == AV_LOG_WARNING)
        num_warnings++;
}