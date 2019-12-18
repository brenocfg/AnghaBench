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
struct TYPE_3__ {int /*<<< orphan*/ * strings; scalar_t__ max_strings; scalar_t__ num_strings; } ;
typedef  TYPE_1__ STRING_VEC_T ;

/* Variables and functions */

void string_vec_init(STRING_VEC_T *vec)
{
    vec->num_strings = 0;
    vec->max_strings = 0;
    vec->strings = NULL;
}