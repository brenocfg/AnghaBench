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
typedef  int /*<<< orphan*/  gsize ;
typedef  int /*<<< orphan*/  gconstpointer ;
typedef  int /*<<< orphan*/  GhbValue ;
typedef  int /*<<< orphan*/  GResource ;
typedef  int /*<<< orphan*/  GBytes ;

/* Variables and functions */
 int /*<<< orphan*/  g_bytes_get_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_bytes_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_resource_lookup_data (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_data_get_resource () ; 
 int /*<<< orphan*/  ghb_data_register_resource () ; 
 int /*<<< orphan*/  ghb_dict_new () ; 
 int /*<<< orphan*/  ghb_dict_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_json_parse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resources ; 

void
ghb_resource_init()
{
    GhbValue *val;
    gsize data_size;
    GBytes *gbytes;
    gconstpointer data;

    resources = ghb_dict_new();

    ghb_data_register_resource();
    GResource *data_res = ghb_data_get_resource();

    gbytes = g_resource_lookup_data(data_res,
                    "/fr/handbrake/ghb/data/internal_defaults.json", 0, NULL);
    data = g_bytes_get_data(gbytes, &data_size);
    val = ghb_json_parse(data);
    g_bytes_unref(gbytes);
    ghb_dict_set(resources, "internal-defaults", val);

    gbytes = g_resource_lookup_data(data_res,
                    "/fr/handbrake/ghb/data/widget.deps", 0, NULL);
    data = g_bytes_get_data(gbytes, &data_size);
    val = ghb_json_parse(data);
    g_bytes_unref(gbytes);
    ghb_dict_set(resources, "widget-deps", val);

    gbytes = g_resource_lookup_data(data_res,
                    "/fr/handbrake/ghb/data/widget_reverse.deps", 0, NULL);
    data = g_bytes_get_data(gbytes, &data_size);
    val = ghb_json_parse(data);
    g_bytes_unref(gbytes);
    ghb_dict_set(resources, "widget-reverse-deps", val);
}