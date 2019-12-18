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
 int /*<<< orphan*/  ghb_dict_set (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_string_value_new (int /*<<< orphan*/  const*) ; 

void
ghb_dict_set_string(GhbValue *dict, const gchar *key, const gchar *sval)
{
    GhbValue *value;
    value = ghb_string_value_new(sval);
    ghb_dict_set(dict, key, value);
}