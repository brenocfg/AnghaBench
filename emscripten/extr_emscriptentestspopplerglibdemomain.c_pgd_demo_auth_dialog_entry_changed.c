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
typedef  int /*<<< orphan*/  GtkEditable ;
typedef  int /*<<< orphan*/  GtkDialog ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_ENTRY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_RESPONSE_OK ; 
 int /*<<< orphan*/  G_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_set_data (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_dialog_set_response_sensitive (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 char* gtk_entry_get_text (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pgd_demo_auth_dialog_entry_changed (GtkEditable *editable,
				    GtkDialog   *dialog)
{
	const char *text;

	text = gtk_entry_get_text (GTK_ENTRY (editable));

	gtk_dialog_set_response_sensitive (dialog, GTK_RESPONSE_OK,
					   (text != NULL && *text != '\0'));
	g_object_set_data (G_OBJECT (dialog), "pgd-password", (gpointer)text);
}