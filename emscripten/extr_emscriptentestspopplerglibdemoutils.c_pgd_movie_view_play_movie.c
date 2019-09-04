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
typedef  int /*<<< orphan*/  const gchar ;
typedef  int /*<<< orphan*/  PopplerMovie ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GFile ;

/* Variables and functions */
 int /*<<< orphan*/  GDK_CURRENT_TIME ; 
 int /*<<< orphan*/  const* g_build_filename (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* g_file_get_uri (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_file_new_for_path (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * g_file_new_for_uri (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* g_get_current_dir () ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 scalar_t__ g_path_is_absolute (int /*<<< orphan*/  const*) ; 
 scalar_t__ g_strrstr (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  gtk_show_uri (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_get_screen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* poppler_movie_get_filename (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_movie_view_play_movie (GtkWidget    *button,
			   PopplerMovie *movie)
{
	const gchar *filename;
	GFile       *file;
	gchar       *uri;

	filename = poppler_movie_get_filename (movie);
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

	uri = g_file_get_uri (file);
	g_object_unref (file);
	if (uri) {
		gtk_show_uri (gtk_widget_get_screen (button),
			      uri, GDK_CURRENT_TIME, NULL);
		g_free (uri);
	}
}