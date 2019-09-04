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
 int /*<<< orphan*/  REPORT_RESULT (int) ; 
 int /*<<< orphan*/  emscripten_get_element_css_size (int /*<<< orphan*/ *,double*,double*) ; 
 scalar_t__ isnan (double) ; 

int main() 
{
    int result = 0;
    double w, h;
    emscripten_get_element_css_size(NULL, &w, &h);
    if (isnan(w) || isnan(h))
    {
        result = 1;
    }
    REPORT_RESULT(result);
    return 0;
}