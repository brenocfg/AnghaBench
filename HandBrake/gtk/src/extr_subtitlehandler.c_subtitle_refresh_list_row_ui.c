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
typedef  scalar_t__ gint ;
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GhbValue ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_TREE_STORE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup (char*) ; 
 char* g_strdup_printf (char*,scalar_t__) ; 
 int /*<<< orphan*/  g_string_append_printf (int /*<<< orphan*/ *,char*,...) ; 
 char* g_string_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_string_new (char*) ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ghb_dict_get_bool (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ gtk_tree_model_iter_children (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_store_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,char*,int,...) ; 
 char* subtitle_get_track_description (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
subtitle_refresh_list_row_ui(
    GtkTreeModel *tm,
    GtkTreeIter *ti,
    GhbValue *settings,
    GhbValue *subsettings)
{
    GtkTreeIter cti;
    gboolean forced, burned, def;
    char *info_src, *info_src_2;
    char *info_dst, *info_dst_2;
    char *desc;


    info_src_2 = NULL;
    info_dst_2 = NULL;

    forced = ghb_dict_get_bool(subsettings, "Forced");
    burned = ghb_dict_get_bool(subsettings, "Burn");
    def = ghb_dict_get_bool(subsettings, "Default");
    desc = subtitle_get_track_description(settings, subsettings);
    info_src = g_strdup_printf("<small>%s</small>", desc);
    g_free(desc);
    if (ghb_dict_get(subsettings, "Import") != NULL)
    {
        gint offset;
        offset = ghb_dict_get_int(subsettings, "Offset");
        if (offset != 0)
        {
            info_dst_2 = g_strdup_printf("Offset: %dms", offset);
        }
    }

    GString *str = g_string_new("<small>");
    g_string_append_printf(str, "%s ", burned ? "Burned Into Video" :
                                                "Passthrough");
    if (forced)
    {
        g_string_append_printf(str, "(Forced Subtitles Only)");
    }
    if (def)
    {
        g_string_append_printf(str, "(Default)");
    }
    g_string_append_printf(str, "</small>");

    info_dst = g_string_free(str, FALSE);

    gtk_tree_store_set(GTK_TREE_STORE(tm), ti,
        // These are displayed in list
        0, info_src,
        1, "-->",
        2, info_dst,
        3, "hb-edit",
        4, "hb-remove",
        5, 0.5,
        -1);

    if (info_src_2 != NULL || info_dst_2 != NULL)
    {
        if (info_src_2 == NULL)
            info_src_2 = g_strdup("");
        if (info_dst_2 == NULL)
            info_dst_2 = g_strdup("");

        if (!gtk_tree_model_iter_children(tm, &cti, ti))
        {
            gtk_tree_store_append(GTK_TREE_STORE(tm), &cti, ti);
        }
        gtk_tree_store_set(GTK_TREE_STORE(tm), &cti,
            // These are displayed in list
            0, info_src_2,
            2, info_dst_2,
            5, 0.0,
            -1);
    }
    else
    {
        if (gtk_tree_model_iter_children(tm, &cti, ti))
        {
            gtk_tree_store_remove(GTK_TREE_STORE(tm), &cti);
        }
    }

    g_free(info_src);
    g_free(info_src_2);
    g_free(info_dst);
    g_free(info_dst_2);
}