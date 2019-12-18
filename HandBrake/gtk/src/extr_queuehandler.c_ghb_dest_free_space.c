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
typedef  int guint64 ;
typedef  int gint64 ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GhbValue ;
typedef  int /*<<< orphan*/  GFileInfo ;
typedef  int /*<<< orphan*/  GFile ;

/* Variables and functions */
 int /*<<< orphan*/  G_FILE_ATTRIBUTE_FILESYSTEM_FREE ; 
 int g_file_info_get_attribute_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ g_file_info_has_attribute (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_file_new_for_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_file_query_filesystem_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_path_get_dirname (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ghb_dict_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ghb_resolve_symlink (int /*<<< orphan*/ *) ; 

gint64
ghb_dest_free_space(GhbValue *settings)
{
    GFile       *gfile;
    GFileInfo   *info;
    guint64      size = -1;
    const gchar *dest     = ghb_dict_get_string(settings, "destination");
    gchar       *destdir  = g_path_get_dirname(dest);
    gchar       *resolved = ghb_resolve_symlink(destdir);

    gfile = g_file_new_for_path(resolved);
    info  = g_file_query_filesystem_info(gfile,
                                G_FILE_ATTRIBUTE_FILESYSTEM_FREE, NULL, NULL);
    if (info != NULL)
    {
        if (g_file_info_has_attribute(info, G_FILE_ATTRIBUTE_FILESYSTEM_FREE))
        {
            size = g_file_info_get_attribute_uint64(info,
                                    G_FILE_ATTRIBUTE_FILESYSTEM_FREE);
        }
        g_object_unref(info);
    }
    g_object_unref(gfile);
    g_free(resolved);
    g_free(destdir);

    return size;
}