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

/* Variables and functions */
 int /*<<< orphan*/  hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * hb_value_array_get (int /*<<< orphan*/ *,int) ; 
 int hb_value_array_len (int /*<<< orphan*/ *) ; 
 int hb_value_get_int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int has_default_subtitle(hb_value_array_t *list)
{
    int ii, count, def;

    count = hb_value_array_len(list);
    for (ii = 0; ii < count; ii++)
    {
        hb_value_t *sub = hb_value_array_get(list, ii);
        def = hb_value_get_int(hb_dict_get(sub, "Default"));
        if (def)
        {
            return def;
        }
    }
    return 0;
}