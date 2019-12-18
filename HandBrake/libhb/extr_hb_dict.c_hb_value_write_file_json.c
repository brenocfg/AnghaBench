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
typedef  int /*<<< orphan*/  hb_value_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int JSON_INDENT (int) ; 
 int JSON_SORT_KEYS ; 
 int json_dumpf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int  hb_value_write_file_json(hb_value_t *value, FILE *file)
{
    return json_dumpf(value, file, JSON_INDENT(4) | JSON_SORT_KEYS);
}