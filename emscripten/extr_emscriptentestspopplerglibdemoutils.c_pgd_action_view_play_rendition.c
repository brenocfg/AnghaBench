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
typedef  int gint ;
typedef  int /*<<< orphan*/  const gchar ;
typedef  int /*<<< orphan*/  PopplerMedia ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GFile ;
typedef  int /*<<< orphan*/  GDestroyNotify ;

/* Variables and functions */
 int /*<<< orphan*/  GDK_CURRENT_TIME ; 
 int /*<<< orphan*/  GINT_TO_POINTER (int) ; 
 int /*<<< orphan*/  G_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ free_tmp_file ; 
 int /*<<< orphan*/  const* g_build_filename (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* g_file_get_uri (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_file_new_for_path (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * g_file_new_for_uri (int /*<<< orphan*/  const*) ; 
 int g_file_open_tmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* g_get_current_dir () ; 
 int /*<<< orphan*/  g_object_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_set_data_full (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 scalar_t__ g_path_is_absolute (int /*<<< orphan*/  const*) ; 
 scalar_t__ g_strrstr (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  gtk_show_uri (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_get_screen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* poppler_media_get_filename (int /*<<< orphan*/ *) ; 
 scalar_t__ poppler_media_is_embedded (int /*<<< orphan*/ *) ; 
 scalar_t__ poppler_media_save_to_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  save_helper ; 

__attribute__((used)) static void
pgd_action_view_play_rendition (GtkWidget    *button,
				PopplerMedia *media)
{
	GFile *file = NULL;
	gchar *uri;

	if (poppler_media_is_embedded (media)) {
		gint   fd;
		gchar *tmp_filename = NULL;

		fd = g_file_open_tmp (NULL, &tmp_filename, NULL);
		if (fd != -1) {
			if (poppler_media_save_to_callback (media, save_helper, GINT_TO_POINTER (fd), NULL)) {
				file = g_file_new_for_path (tmp_filename);
				g_object_set_data_full (G_OBJECT (media),
							"tmp-file", g_object_ref (file),
							(GDestroyNotify)free_tmp_file);
			} else {
				g_free (tmp_filename);
			}
			close (fd);
		} else if (tmp_filename) {
			g_free (tmp_filename);
		}

	} else {
		const gchar *filename;

		filename = poppler_media_get_filename (media);
		if (g_path_is_absolute (filename)) {
			file = g_file_new_for_path (filename);
		} else if (g_strrstr (filename, "://")) {
			file = g_file_new_for_uri (filename);
		} else {
			gchar *cwd;
			gchar *path;

			// FIXME: relative to doc uri, not cwd
			cwd = g_get_current_dir ();
			path = g_build_filename (cwd, filename, NULL);
			g_free (cwd);

			file = g_file_new_for_path (path);
			g_free (path);
		}
	}

	if (file) {
		uri = g_file_get_uri (file);
		g_object_unref (file);
		if (uri) {
			gtk_show_uri (gtk_widget_get_screen (button),
				      uri, GDK_CURRENT_TIME, NULL);
			g_free (uri);
		}
	}
}