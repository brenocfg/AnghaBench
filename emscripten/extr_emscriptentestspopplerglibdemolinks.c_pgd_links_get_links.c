#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gint ;
typedef  char gchar ;
struct TYPE_22__ {int /*<<< orphan*/  value_name; } ;
struct TYPE_21__ {scalar_t__ data; } ;
struct TYPE_20__ {int /*<<< orphan*/  model; int /*<<< orphan*/  timer_label; int /*<<< orphan*/  page; int /*<<< orphan*/  doc; int /*<<< orphan*/  action_view; } ;
struct TYPE_19__ {int /*<<< orphan*/  type; } ;
struct TYPE_17__ {int /*<<< orphan*/  y2; int /*<<< orphan*/  x2; int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; } ;
struct TYPE_18__ {TYPE_1__ area; int /*<<< orphan*/  action; } ;
typedef  int /*<<< orphan*/  PopplerPage ;
typedef  TYPE_2__ PopplerLinkMapping ;
typedef  TYPE_3__ PopplerAction ;
typedef  TYPE_4__ PgdLinksDemo ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GWeakNotify ;
typedef  int /*<<< orphan*/  GTimer ;
typedef  TYPE_5__ GList ;
typedef  TYPE_6__ GEnumValue ;
typedef  int /*<<< orphan*/  GEnumClass ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_LABEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_OBJECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LINKS_ACTION_COLUMN ; 
 int /*<<< orphan*/  LINKS_ACTION_TYPE_COLUMN ; 
 int /*<<< orphan*/  LINKS_X1_COLUMN ; 
 int /*<<< orphan*/  LINKS_X2_COLUMN ; 
 int /*<<< orphan*/  LINKS_Y1_COLUMN ; 
 int /*<<< orphan*/  LINKS_Y2_COLUMN ; 
 int /*<<< orphan*/  POPPLER_TYPE_ACTION_TYPE ; 
 TYPE_6__* g_enum_get_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ g_list_length (TYPE_5__*) ; 
 TYPE_5__* g_list_next (TYPE_5__*) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_weak_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 char* g_strdup_printf (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  g_timer_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_timer_elapsed (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_timer_new () ; 
 int /*<<< orphan*/  g_timer_stop (int /*<<< orphan*/ *) ; 
 scalar_t__ g_type_class_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_label_set_markup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_list_store_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_list_store_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_list_store_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  pgd_action_view_set_action (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* poppler_action_copy (int /*<<< orphan*/ ) ; 
 scalar_t__ poppler_action_free ; 
 int /*<<< orphan*/ * poppler_document_get_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poppler_page_free_link_mapping (TYPE_5__*) ; 
 TYPE_5__* poppler_page_get_link_mapping (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_links_get_links (GtkWidget    *button,
		     PgdLinksDemo *demo)
{
	PopplerPage *page;
	GList       *mapping, *l;
	gint         n_links;
	GTimer      *timer;
	
	gtk_list_store_clear (demo->model);
	pgd_action_view_set_action (demo->action_view, NULL);

	page = poppler_document_get_page (demo->doc, demo->page);
	if (!page)
		return;

	timer = g_timer_new ();
	mapping = poppler_page_get_link_mapping (page);
	g_timer_stop (timer);

	n_links = g_list_length (mapping);
	if (n_links > 0) {
		gchar *str;
		
		str = g_strdup_printf ("<i>%d links found in %.4f seconds</i>",
				       n_links, g_timer_elapsed (timer, NULL));
		gtk_label_set_markup (GTK_LABEL (demo->timer_label), str);
		g_free (str);
	} else {
		gtk_label_set_markup (GTK_LABEL (demo->timer_label), "<i>No links found</i>");
	}

	g_timer_destroy (timer);

	for (l = mapping; l; l = g_list_next (l)) {
		PopplerLinkMapping *lmapping;
		PopplerAction      *action;
		GEnumValue         *enum_value;
		GtkTreeIter         iter;
		gchar              *x1, *y1, *x2, *y2;

		lmapping = (PopplerLinkMapping *)l->data;
		action = poppler_action_copy (lmapping->action);
		enum_value = g_enum_get_value ((GEnumClass *) g_type_class_ref (POPPLER_TYPE_ACTION_TYPE), action->type);

		x1 = g_strdup_printf ("%.2f", lmapping->area.x1);
		y1 = g_strdup_printf ("%.2f", lmapping->area.y1);
		x2 = g_strdup_printf ("%.2f", lmapping->area.x2);
		y2 = g_strdup_printf ("%.2f", lmapping->area.y2);

		gtk_list_store_append (demo->model, &iter);
		gtk_list_store_set (demo->model, &iter,
				    LINKS_ACTION_TYPE_COLUMN, enum_value->value_name,
				    LINKS_X1_COLUMN, x1, 
				    LINKS_Y1_COLUMN, y1,
				    LINKS_X2_COLUMN, x2,
				    LINKS_Y2_COLUMN, y2,
				    LINKS_ACTION_COLUMN, action,
				    -1);
		g_free (x1);
		g_free (y1);
		g_free (x2);
		g_free (y2);
		
		g_object_weak_ref (G_OBJECT (demo->model),
				   (GWeakNotify)poppler_action_free,
				   action);
	}

	poppler_page_free_link_mapping (mapping);
	g_object_unref (page);
}