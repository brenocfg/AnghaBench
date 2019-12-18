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
typedef  int /*<<< orphan*/  hb_value_array_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int /*<<< orphan*/ * hb_dict_init () ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void hb_avfilter_append_dict(hb_value_array_t * filters,
                           const char * name, hb_value_t * settings)
{
    hb_dict_t * filter_dict = hb_dict_init();

    hb_dict_set(filter_dict, name, settings);
    hb_value_array_append(filters, filter_dict);
}