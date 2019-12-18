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
typedef  int /*<<< orphan*/  GtkRange ;

/* Variables and functions */
 int /*<<< orphan*/  g_key_file_set_integer (int /*<<< orphan*/ ,char*,char*,int) ; 
 scalar_t__ gtk_range_get_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  keyfile ; 

__attribute__((used)) static void volume_changed(GtkRange * range, gpointer data) {
    g_key_file_set_integer(keyfile, "General", "Volume", (int) gtk_range_get_value(range));
}