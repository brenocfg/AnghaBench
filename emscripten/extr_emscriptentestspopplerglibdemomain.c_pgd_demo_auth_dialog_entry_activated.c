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
typedef  int /*<<< orphan*/  GtkEntry ;
typedef  int /*<<< orphan*/  GtkDialog ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_RESPONSE_OK ; 
 int /*<<< orphan*/  gtk_dialog_response (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pgd_demo_auth_dialog_entry_activated (GtkEntry  *entry,
				      GtkDialog *dialog)
{
	gtk_dialog_response (dialog, GTK_RESPONSE_OK);
}