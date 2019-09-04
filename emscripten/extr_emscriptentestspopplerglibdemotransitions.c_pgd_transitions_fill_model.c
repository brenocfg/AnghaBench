#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gint ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_8__ {int /*<<< orphan*/  doc; int /*<<< orphan*/  treeview; } ;
struct TYPE_7__ {scalar_t__ duration; scalar_t__ angle; scalar_t__ scale; scalar_t__ rectangular; int /*<<< orphan*/  direction; int /*<<< orphan*/  alignment; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ PopplerPageTransition ;
typedef  int /*<<< orphan*/  PopplerPage ;
typedef  TYPE_2__ PgdTransitionsDemo ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_LIST_STORE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRANSITIONS_ALIGNMENT_COLUMN ; 
 int /*<<< orphan*/  TRANSITIONS_ANGLE_COLUMN ; 
 int /*<<< orphan*/  TRANSITIONS_DIRECTION_COLUMN ; 
 int /*<<< orphan*/  TRANSITIONS_DURATION_COLUMN ; 
 int /*<<< orphan*/  TRANSITIONS_PAGE_COLUMN ; 
 int /*<<< orphan*/  TRANSITIONS_RECTANGULAR_COLUMN ; 
 int /*<<< orphan*/  TRANSITIONS_SCALE_COLUMN ; 
 int /*<<< orphan*/  TRANSITIONS_TYPE_COLUMN ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup_printf (char*,scalar_t__) ; 
 scalar_t__ gtk_events_pending () ; 
 int /*<<< orphan*/  gtk_list_store_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gtk_main_iteration () ; 
 int /*<<< orphan*/ * gtk_tree_view_get_model (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_transitions_update_progress (TYPE_2__*,scalar_t__,scalar_t__) ; 
 scalar_t__ poppler_document_get_n_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * poppler_document_get_page (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* poppler_page_get_transition (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poppler_page_transition_free (TYPE_1__*) ; 
 int /*<<< orphan*/  transition_alignment_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transition_direction_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transition_type_to_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean
pgd_transitions_fill_model (PgdTransitionsDemo *demo)
{
	GtkTreeModel *model;
	gint          i, n_pages;

	n_pages = poppler_document_get_n_pages (demo->doc);

	model = gtk_tree_view_get_model (GTK_TREE_VIEW (demo->treeview));
	g_object_ref (model);

	for (i = 0; i < n_pages; i++) {
		PopplerPage           *page;
		PopplerPageTransition *transition;

		pgd_transitions_update_progress (demo, n_pages, i);

		while (gtk_events_pending ())
			gtk_main_iteration ();

		page = poppler_document_get_page (demo->doc, i);
		if (!page)
			continue;

		transition = poppler_page_get_transition (page);
		if (transition) {
			GtkTreeIter iter;
			gchar      *npage;
			gchar      *duration;
			gchar      *angle;
			gchar      *scale;

			npage = g_strdup_printf ("%d", i + 1);
			duration = g_strdup_printf ("%d", transition->duration);
			angle = g_strdup_printf ("%d", transition->angle);
			scale = g_strdup_printf ("%.2f", transition->scale);
			
			gtk_list_store_append (GTK_LIST_STORE (model), &iter);
			gtk_list_store_set (GTK_LIST_STORE (model), &iter,
					    TRANSITIONS_PAGE_COLUMN, npage,
					    TRANSITIONS_TYPE_COLUMN,
					    transition_type_to_string (transition->type),
					    TRANSITIONS_ALIGNMENT_COLUMN,
					    transition_alignment_to_string (transition->alignment),
					    TRANSITIONS_DIRECTION_COLUMN,
					    transition_direction_to_string (transition->direction),
					    TRANSITIONS_DURATION_COLUMN, duration, 
					    TRANSITIONS_ANGLE_COLUMN, angle, 
					    TRANSITIONS_SCALE_COLUMN, scale, 
					    TRANSITIONS_RECTANGULAR_COLUMN,
					    transition->rectangular ? "Yes" : "No",
					    -1);
			g_free (npage);
			g_free (duration);
			g_free (angle);
			g_free (scale);

			poppler_page_transition_free (transition);
		}

		g_object_unref (page);
	}

	pgd_transitions_update_progress (demo, n_pages, n_pages);
	g_object_unref (model);

	return FALSE;
}