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
typedef  int /*<<< orphan*/  GhbValue ;
typedef  int /*<<< orphan*/  GhbDictIter ;

/* Variables and functions */
 scalar_t__ GHB_DICT ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  ghb_dict_iter_init (int /*<<< orphan*/  const*) ; 
 scalar_t__ ghb_dict_iter_next (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ghb_dict_set (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_value_dup (int /*<<< orphan*/ *) ; 
 scalar_t__ ghb_value_type (int /*<<< orphan*/ *) ; 

void
ghb_dict_copy(GhbValue *dst, const GhbValue *src)
{
    GhbDictIter iter;
    const char *key;
    GhbValue *val, *dst_val;

    iter = ghb_dict_iter_init(src);
    while (ghb_dict_iter_next(src, &iter, &key, &val))
    {
        dst_val = ghb_dict_get(dst, key);
        if (ghb_value_type(val) == GHB_DICT)
        {
            if (dst_val == NULL || ghb_value_type(dst_val) != GHB_DICT)
            {
                dst_val = ghb_value_dup(val);
                ghb_dict_set(dst, key, dst_val);
            }
            else if (ghb_value_type(dst_val) == GHB_DICT)
            {
                ghb_dict_copy(dst_val, val);
            }
        }
        else
        {
            ghb_dict_set(dst, key, ghb_value_dup(val));
        }
    }
}