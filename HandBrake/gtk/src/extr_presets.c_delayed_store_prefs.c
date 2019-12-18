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
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  gboolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  prefsDict ; 
 scalar_t__ prefs_timeout_id ; 
 int /*<<< orphan*/  write_config_file (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean
delayed_store_prefs(gpointer data)
{
    write_config_file("preferences.json", prefsDict);
    prefs_timeout_id = 0;
    return FALSE;
}