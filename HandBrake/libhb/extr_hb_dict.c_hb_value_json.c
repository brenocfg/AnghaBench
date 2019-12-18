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
struct TYPE_3__ {int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ json_error_t ;
typedef  int /*<<< orphan*/  hb_value_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_loads (char const*,int /*<<< orphan*/ ,TYPE_1__*) ; 

hb_value_t * hb_value_json(const char *json)
{
    json_error_t error;
    hb_value_t *val = json_loads(json, 0, &error);
    if (val == NULL)
    {
        hb_error("hb_value_json: Failed, error %s", error.text);
    }
    return val;
}