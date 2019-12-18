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
struct TYPE_3__ {int value_col; int value_len; } ;
typedef  TYPE_1__ VALUE ;

/* Variables and functions */

__attribute__((used)) static int
digit_of(VALUE * data)
{
    int col = data->value_col;
    int result = 1;

    while (++col < data->value_len) {
	result *= 10;
    }
    return result;
}