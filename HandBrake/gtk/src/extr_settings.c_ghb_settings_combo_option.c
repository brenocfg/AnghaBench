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
 int /*<<< orphan*/  ghb_dict_get_value (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ghb_lookup_combo_option (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

gchar*
ghb_settings_combo_option(const GhbValue *settings, const gchar *key)
{
    return ghb_lookup_combo_option(key, ghb_dict_get_value(settings, key));
}