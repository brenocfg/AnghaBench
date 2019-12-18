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
struct TYPE_3__ {scalar_t__ name; int name_y; int text_y; } ;
typedef  TYPE_1__ DIALOG_FORMITEM ;

/* Variables and functions */

__attribute__((used)) static int
form_limit(DIALOG_FORMITEM item[])
{
    int n;
    int limit = 0;
    for (n = 0; item[n].name != 0; ++n) {
	if (limit < item[n].name_y)
	    limit = item[n].name_y;
	if (limit < item[n].text_y)
	    limit = item[n].text_y;
    }
    return limit;
}