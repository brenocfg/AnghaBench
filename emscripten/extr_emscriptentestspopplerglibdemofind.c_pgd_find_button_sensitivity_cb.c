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
typedef  char gchar ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkEntry ;

/* Variables and functions */
 char* gtk_entry_get_text (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
pgd_find_button_sensitivity_cb (GtkWidget *button,
				GtkEntry  *entry)
{
	const gchar *text;

	text = gtk_entry_get_text (entry);
	gtk_widget_set_sensitive (button, text != NULL && text[0] != '\0');
}