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
struct TYPE_3__ {scalar_t__ text_flen; } ;
typedef  TYPE_1__ DIALOG_FORMITEM ;

/* Variables and functions */

__attribute__((used)) static int
is_first_field(DIALOG_FORMITEM item[], int choice)
{
    int count = 0;
    while (choice >= 0) {
	if (item[choice].text_flen > 0) {
	    ++count;
	}
	--choice;
    }

    return (count == 1);
}