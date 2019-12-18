#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {char const* pattern; int /*<<< orphan*/  pattern_ignore_case; } ;
typedef  TYPE_1__ mz_zip_reader ;

/* Variables and functions */

void mz_zip_reader_set_pattern(void *handle, const char *pattern, uint8_t ignore_case)
{
    mz_zip_reader *reader = (mz_zip_reader *)handle;
    reader->pattern = pattern;
    reader->pattern_ignore_case = ignore_case;
}