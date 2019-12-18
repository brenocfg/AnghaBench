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
typedef  int /*<<< orphan*/  GtkBuilder ;
typedef  int /*<<< orphan*/  GObject ;

/* Variables and functions */
 int /*<<< orphan*/  g_message (char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * gtk_builder_get_object (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

GObject*
debug_get_object(GtkBuilder* b, const gchar *n)
{
    g_message("name %s\n", n);
    return gtk_builder_get_object(b, n);
}