#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gint ;
typedef  char gchar ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_31__ {TYPE_12__* state_list; } ;
struct TYPE_30__ {TYPE_12__* media; int /*<<< orphan*/  op; } ;
struct TYPE_29__ {int /*<<< orphan*/  movie; int /*<<< orphan*/  operation; } ;
struct TYPE_28__ {char* named_dest; } ;
struct TYPE_27__ {char* uri; } ;
struct TYPE_26__ {char* file_name; char* params; } ;
struct TYPE_25__ {char* file_name; int /*<<< orphan*/  dest; } ;
struct TYPE_24__ {int /*<<< orphan*/  dest; } ;
struct TYPE_23__ {char* title; } ;
struct TYPE_22__ {scalar_t__ data; } ;
struct TYPE_21__ {int type; TYPE_9__ ocg_state; TYPE_8__ rendition; TYPE_7__ movie; TYPE_6__ named; TYPE_5__ uri; TYPE_4__ launch; TYPE_3__ goto_remote; TYPE_2__ goto_dest; TYPE_1__ any; } ;
struct TYPE_20__ {int /*<<< orphan*/  action; int /*<<< orphan*/  layers; } ;
typedef  TYPE_10__ PopplerActionLayer ;
typedef  TYPE_11__ PopplerAction ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  TYPE_12__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_ALIGNMENT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_BIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_STOCK_MEDIA_PLAY ; 
 int /*<<< orphan*/  GTK_TABLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
#define  POPPLER_ACTION_GOTO_DEST 140 
#define  POPPLER_ACTION_GOTO_REMOTE 139 
#define  POPPLER_ACTION_LAUNCH 138 
#define  POPPLER_ACTION_LAYER_OFF 137 
#define  POPPLER_ACTION_LAYER_ON 136 
#define  POPPLER_ACTION_LAYER_TOGGLE 135 
#define  POPPLER_ACTION_MOVIE 134 
#define  POPPLER_ACTION_NAMED 133 
#define  POPPLER_ACTION_NONE 132 
#define  POPPLER_ACTION_OCG_STATE 131 
#define  POPPLER_ACTION_RENDITION 130 
#define  POPPLER_ACTION_UNKNOWN 129 
#define  POPPLER_ACTION_URI 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_assert_not_reached () ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_list_length (int /*<<< orphan*/ ) ; 
 TYPE_12__* g_list_next (TYPE_12__*) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_12__*) ; 
 char* g_strdup_printf (char*,int /*<<< orphan*/ ) ; 
 char* get_movie_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_alignment_new (double,double,int,int) ; 
 int /*<<< orphan*/  gtk_alignment_set_padding (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/ * gtk_bin_get_child (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_button_new_from_stock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_button_new_with_label (char*) ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_container_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_table_new (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_table_set_col_spacings (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_table_set_row_spacings (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_action_view_add_destination (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_action_view_do_action_layer ; 
 int /*<<< orphan*/  pgd_action_view_play_rendition ; 
 int /*<<< orphan*/ * pgd_movie_view_new () ; 
 int /*<<< orphan*/  pgd_movie_view_set_movie (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_table_add_property (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_table_add_property_with_custom_widget (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* poppler_media_get_filename (TYPE_12__*) ; 
 char* poppler_media_get_mime_type (TYPE_12__*) ; 
 int /*<<< orphan*/  poppler_media_is_embedded (TYPE_12__*) ; 

void
pgd_action_view_set_action (GtkWidget     *action_view,
			    PopplerAction *action)
{
	GtkWidget  *alignment;
	GtkWidget  *table;
	gint        row = 0;

	alignment = gtk_bin_get_child (GTK_BIN (action_view));
	if (alignment) {
		gtk_container_remove (GTK_CONTAINER (action_view), alignment);
	}
	
	alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
	gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 5, 5, 12, 5);
	gtk_container_add (GTK_CONTAINER (action_view), alignment);
	gtk_widget_show (alignment);

	if (!action)
		return;

	table = gtk_table_new (10, 2, FALSE);
	gtk_table_set_col_spacings (GTK_TABLE (table), 6);
	gtk_table_set_row_spacings (GTK_TABLE (table), 6);

	pgd_table_add_property (GTK_TABLE (table), "<b>Title:</b>", action->any.title, &row);
	
	switch (action->type) {
	case POPPLER_ACTION_UNKNOWN:
		pgd_table_add_property (GTK_TABLE (table), "<b>Type:</b>", "Unknown", &row);
		break;
	case POPPLER_ACTION_NONE:
		pgd_table_add_property (GTK_TABLE (table), "<b>Type:</b>", "None", &row);
		break;
	case POPPLER_ACTION_GOTO_DEST:
		pgd_action_view_add_destination (action_view, GTK_TABLE (table), action->goto_dest.dest, FALSE, &row);
		break;
	case POPPLER_ACTION_GOTO_REMOTE:
		pgd_table_add_property (GTK_TABLE (table), "<b>Type:</b>", "Remote Destination", &row);
		pgd_table_add_property (GTK_TABLE (table), "<b>Filename:</b>", action->goto_remote.file_name, &row);
		pgd_action_view_add_destination (action_view, GTK_TABLE (table), action->goto_remote.dest, TRUE, &row);
		break;
	case POPPLER_ACTION_LAUNCH:
		pgd_table_add_property (GTK_TABLE (table), "<b>Type:</b>", "Launch", &row);
		pgd_table_add_property (GTK_TABLE (table), "<b>Filename:</b>", action->launch.file_name, &row);
		pgd_table_add_property (GTK_TABLE (table), "<b>Params:</b>", action->launch.params, &row);
		break;
	case POPPLER_ACTION_URI:
		pgd_table_add_property (GTK_TABLE (table), "<b>Type:</b>", "External URI", &row);
		pgd_table_add_property (GTK_TABLE (table), "<b>URI</b>", action->uri.uri, &row);
		break;
	case POPPLER_ACTION_NAMED:
		pgd_table_add_property (GTK_TABLE (table), "<b>Type:</b>", "Named Action", &row);
		pgd_table_add_property (GTK_TABLE (table), "<b>Name:</b>", action->named.named_dest, &row);
		break;
	case POPPLER_ACTION_MOVIE: {
		GtkWidget *movie_view = pgd_movie_view_new ();

		pgd_table_add_property (GTK_TABLE (table), "<b>Type:</b>", "Movie", &row);
		pgd_table_add_property (GTK_TABLE (table), "<b>Operation:</b>", get_movie_op (action->movie.operation), &row);
		pgd_movie_view_set_movie (movie_view, action->movie.movie);
		pgd_table_add_property_with_custom_widget (GTK_TABLE (table), "<b>Movie:</b>", movie_view, &row);
	}
		break;
	case POPPLER_ACTION_RENDITION: {
		gchar *text;

		pgd_table_add_property (GTK_TABLE (table), "<b>Type:</b>", "Rendition", &row);
		text = g_strdup_printf ("%d", action->rendition.op);
		pgd_table_add_property (GTK_TABLE (table), "<b>Operation:</b>", text, &row);
		g_free (text);
		if (action->rendition.media) {
			gboolean   embedded = poppler_media_is_embedded (action->rendition.media);
			GtkWidget *button;

			pgd_table_add_property (GTK_TABLE (table), "<b>Embedded:</b>", embedded ? "Yes": "No", &row);
			if (embedded) {
				const gchar *mime_type = poppler_media_get_mime_type (action->rendition.media);
				pgd_table_add_property (GTK_TABLE (table), "<b>Mime type:</b>",
							mime_type ? mime_type : "",
							&row);
			} else {
				pgd_table_add_property (GTK_TABLE (table), "<b>Filename:</b>",
							poppler_media_get_filename (action->rendition.media),
							&row);
			}

			button = gtk_button_new_from_stock (GTK_STOCK_MEDIA_PLAY);
			g_signal_connect (button, "clicked",
					  G_CALLBACK (pgd_action_view_play_rendition),
					  action->rendition.media);
			pgd_table_add_property_with_custom_widget (GTK_TABLE (table), NULL, button, &row);
			gtk_widget_show (button);
		}
	}
		break;
	case POPPLER_ACTION_OCG_STATE: {
		GList     *l;
		GtkWidget *button;

		pgd_table_add_property (GTK_TABLE (table), "<b>Type:</b>", "OCGState", &row);

		for (l = action->ocg_state.state_list; l; l = g_list_next (l)) {
			PopplerActionLayer *action_layer = (PopplerActionLayer *)l->data;
			gchar *text;
			gint   n_layers = g_list_length (action_layer->layers);

			switch (action_layer->action) {
			case POPPLER_ACTION_LAYER_ON:
				text = g_strdup_printf ("%d layers On", n_layers);
				break;
			case POPPLER_ACTION_LAYER_OFF:
				text = g_strdup_printf ("%d layers Off", n_layers);
				break;
			case POPPLER_ACTION_LAYER_TOGGLE:
				text = g_strdup_printf ("%d layers Toggle", n_layers);
				break;
			}
			pgd_table_add_property (GTK_TABLE (table), "<b>Action:</b>", text, &row);
			g_free (text);
		}

		button = gtk_button_new_with_label ("Do action");
		g_signal_connect (button, "clicked",
				  G_CALLBACK (pgd_action_view_do_action_layer),
				  action->ocg_state.state_list);
		pgd_table_add_property_with_custom_widget (GTK_TABLE (table), NULL, button, &row);
		gtk_widget_show (button);
	}
		break;
	default:
		g_assert_not_reached ();
	}

	gtk_container_add (GTK_CONTAINER (alignment), table);
	gtk_widget_show (table);
}