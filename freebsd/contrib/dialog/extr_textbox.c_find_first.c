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
struct TYPE_3__ {long page_length; } ;
typedef  TYPE_1__ MY_OBJ ;

/* Variables and functions */

__attribute__((used)) static long
find_first(MY_OBJ * obj, char *buffer, long length)
{
    long recount = obj->page_length;
    long result = 0;

    while (length > 0) {
	if (buffer[length] == '\n') {
	    if (--recount < 0) {
		result = length;
		break;
	    }
	}
	--length;
    }
    return result;
}