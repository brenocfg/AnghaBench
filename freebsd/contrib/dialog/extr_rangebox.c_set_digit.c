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
struct TYPE_3__ {int value_len; int current; size_t value_col; scalar_t__ min_value; scalar_t__ max_value; } ;
typedef  TYPE_1__ VALUE ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 long strtol (char*,char**,int) ; 

__attribute__((used)) static bool
set_digit(VALUE * data, int chr)
{
    bool result = FALSE;
    char buffer[80];
    long check;
    char *next = 0;

    sprintf(buffer, "%*d", data->value_len, data->current);
    buffer[data->value_col] = (char) chr;
    check = strtol(buffer, &next, 10);
    if (next == 0 || *next == '\0') {
	if ((check <= (long) data->max_value) &&
	    (check >= (long) data->min_value)) {
	    result = TRUE;
	    data->current = (int) check;
	}
    }

    return result;
}