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
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_2__ {int aspect_ratio; } ;

/* Variables and functions */
 int SCOLS ; 
 int SLINES ; 
 TYPE_1__ dialog_state ; 
 int /*<<< orphan*/  justify_text (int /*<<< orphan*/ *,char const*,int,int,int*,int*) ; 

__attribute__((used)) static void
auto_size_preformatted(const char *prompt, int *height, int *width)
{
    int high = 0, wide = 0;
    float car;			/* Calculated Aspect Ratio */
    float diff;
    int max_y = SLINES - 1;
    int max_x = SCOLS - 2;
    int max_width = max_x;
    int ar = dialog_state.aspect_ratio;

    /* Get the initial dimensions */
    justify_text((WINDOW *) 0, prompt, max_y, max_x, &high, &wide);
    car = (float) (wide / high);

    /*
     * If the aspect ratio is greater than it should be, then decrease the
     * width proportionately.
     */
    if (car > ar) {
	diff = car / (float) ar;
	max_x = (int) ((float) wide / diff + 4);
	justify_text((WINDOW *) 0, prompt, max_y, max_x, &high, &wide);
	car = (float) wide / (float) high;
    }

    /*
     * If the aspect ratio is too small after decreasing the width, then
     * incrementally increase the width until the aspect ratio is equal to or
     * greater than the specified aspect ratio.
     */
    while (car < ar && max_x < max_width) {
	max_x += 4;
	justify_text((WINDOW *) 0, prompt, max_y, max_x, &high, &wide);
	car = (float) (wide / high);
    }

    *height = high;
    *width = wide;
}