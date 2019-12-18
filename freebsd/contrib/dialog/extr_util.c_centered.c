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
 int dlg_count_real_columns (char const*) ; 

__attribute__((used)) static int
centered(int width, const char *string)
{
    int need = dlg_count_real_columns(string);
    int left;

    left = (width - need) / 2 - 1;
    if (left < 0)
	left = 0;
    return left;
}