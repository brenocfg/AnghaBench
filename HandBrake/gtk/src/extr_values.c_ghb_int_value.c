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
typedef  int /*<<< orphan*/  gint64 ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/ * json_integer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_integer_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

GhbValue*
ghb_int_value(gint64 ival)
{
    static GhbValue *gval = NULL;
    if (gval == NULL)
        gval = json_integer(ival);
    else
        json_integer_set(gval, ival);
    return gval;
}