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
typedef  int /*<<< orphan*/  GSourceFunc ;
typedef  int /*<<< orphan*/  GSource ;
typedef  int /*<<< orphan*/  GMainContext ;

/* Variables and functions */
 scalar_t__ delayed_store_prefs ; 
 int /*<<< orphan*/ * g_main_context_default () ; 
 int /*<<< orphan*/ * g_main_context_find_source_by_id (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  g_source_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ g_timeout_add_seconds (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ prefs_timeout_id ; 

__attribute__((used)) static void
store_prefs(void)
{
    if (prefs_timeout_id != 0)
    {
        GMainContext *mc;
        GSource *source;

        mc = g_main_context_default();
        source = g_main_context_find_source_by_id(mc, prefs_timeout_id);
        if (source != NULL)
            g_source_destroy(source);
    }
    prefs_timeout_id = g_timeout_add_seconds(1, (GSourceFunc)delayed_store_prefs, NULL);
}