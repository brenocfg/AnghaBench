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
typedef  int /*<<< orphan*/  json_error_t ;
typedef  int /*<<< orphan*/  hb_value_t ;

/* Variables and functions */
 int /*<<< orphan*/ * json_load_file (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

hb_value_t * hb_value_read_json(const char *path)
{
    json_error_t error;
    hb_value_t *val = json_load_file(path, 0, &error);
    return val;
}