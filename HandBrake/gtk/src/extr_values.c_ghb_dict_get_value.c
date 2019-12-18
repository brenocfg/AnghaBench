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
 int /*<<< orphan*/  g_debug (char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

GhbValue*
ghb_dict_get_value(const GhbValue *dict, const gchar *key)
{
    GhbValue *value;
    value = ghb_dict_get(dict, key);
    if (value == NULL)
        g_debug("returning null (%s)", key);
    return value;
}