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
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/ * json_string (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  json_string_set (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

GhbValue*
ghb_string_value(const gchar *str)
{
    static GhbValue *gval = NULL;
    if (gval == NULL)
        gval = json_string(str);
    else
        json_string_set(gval, str);
    return gval;
}