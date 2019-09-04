#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ guint8 ;
typedef  scalar_t__ gsize ;
typedef  int /*<<< orphan*/  gpointer ;
typedef  scalar_t__ gint ;
typedef  scalar_t__ gboolean ;
struct TYPE_7__ {TYPE_1__* checksum; } ;
struct TYPE_6__ {scalar_t__ len; scalar_t__* str; } ;
typedef  TYPE_2__ PopplerAttachment ;
typedef  int /*<<< orphan*/  GtkTreeView ;
typedef  int /*<<< orphan*/  GtkTreeSelection ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkButton ;
typedef  int /*<<< orphan*/  GChecksum ;

/* Variables and functions */
 int /*<<< orphan*/  ATTACHMENTS_ATTACHMENT_COLUMN ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GTK_WIDGET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_CHECKSUM_MD5 ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  attachment_save_callback ; 
 int /*<<< orphan*/  g_checksum_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_checksum_get_digest (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/ * g_checksum_new (int /*<<< orphan*/ ) ; 
 scalar_t__ g_checksum_type_get_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (scalar_t__*) ; 
 scalar_t__ g_malloc (scalar_t__) ; 
 int /*<<< orphan*/  g_object_unref (TYPE_2__*) ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__**,int) ; 
 int /*<<< orphan*/  gtk_tree_selection_get_selected (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_selection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_get_toplevel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  message_dialog_run (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  poppler_attachment_save_to_callback (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_attachments_validate_button_clicked (GtkButton   *button,
					 GtkTreeView *treeview)
{
	GtkTreeSelection  *selection;
	GtkTreeModel      *model;
	GtkTreeIter        iter;
	GChecksum         *cs;
	guint8            *digest;
	gsize              digest_len;
	PopplerAttachment *attachment;
	gboolean           valid = TRUE;

	selection = gtk_tree_view_get_selection (treeview);
	if (!gtk_tree_selection_get_selected (selection, &model, &iter))
		return;

	gtk_tree_model_get (model, &iter,
			    ATTACHMENTS_ATTACHMENT_COLUMN, &attachment,
			    -1);

	if (!attachment)
		return;

	if (attachment->checksum->len == 0) {
		message_dialog_run (GTK_WINDOW (gtk_widget_get_toplevel (GTK_WIDGET (treeview))),
				    "Impossible to validate attachment: checksum is not available");
		g_object_unref (attachment);

		return;
	}
	
	cs = g_checksum_new (G_CHECKSUM_MD5);
	poppler_attachment_save_to_callback (attachment, attachment_save_callback,
					     (gpointer)cs, NULL);
	digest_len = g_checksum_type_get_length (G_CHECKSUM_MD5);
	digest = (guint8 *) g_malloc (digest_len);
	g_checksum_get_digest (cs, digest, &digest_len);
	g_checksum_free (cs);

	if (attachment->checksum->len == digest_len) {
		gint i;
	
		for (i = 0; i < digest_len; i++) {
			if ((guint8)attachment->checksum->str[i] != digest[i]) {
				valid = FALSE;
				break;
			}
		}
	}

	if (valid) {
		message_dialog_run (GTK_WINDOW (gtk_widget_get_toplevel (GTK_WIDGET (treeview))),
				    "Attachment is valid");
	} else {
		message_dialog_run (GTK_WINDOW (gtk_widget_get_toplevel (GTK_WIDGET (treeview))),
				    "Attachment is not valid: the checksum does not match");
	}

	g_free (digest);
	g_object_unref (attachment);
}