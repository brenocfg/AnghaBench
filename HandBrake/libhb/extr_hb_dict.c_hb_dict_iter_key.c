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
typedef  int /*<<< orphan*/  hb_dict_iter_t ;

/* Variables and functions */
 char const* json_object_iter_key (int /*<<< orphan*/  const) ; 

const char * hb_dict_iter_key(const hb_dict_iter_t iter)
{
    return json_object_iter_key(iter);
}