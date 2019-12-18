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
struct TYPE_2__ {char* column_separator; } ;

/* Variables and functions */
 TYPE_1__ dialog_vars ; 

__attribute__((used)) static char *
column_separator(void)
{
    char *result = 0;

    if ((result = dialog_vars.column_separator) != 0) {
	if (*result == '\0')
	    result = 0;
    }
    return result;
}