#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sysname ;
struct texture_image {int /*<<< orphan*/ * pixels; int /*<<< orphan*/  supports_rgba; scalar_t__ height; scalar_t__ width; } ;
struct TYPE_10__ {int /*<<< orphan*/  content_icon; int /*<<< orphan*/  icon; } ;
typedef  TYPE_1__ stripes_node_t ;
struct TYPE_11__ {float categories_x_pos; float categories_passive_width; int depth; int x; int icon_size; int /*<<< orphan*/  horizontal_list; scalar_t__ categories_selection_ptr; } ;
typedef  TYPE_2__ stripes_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  APPLICATION_SPECIAL_DIRECTORY_ASSETS_XMB_ICONS ; 
 int /*<<< orphan*/  MENU_LIST_HORIZONTAL ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  TEXTURE_FILTER_MIPMAP_LINEAR ; 
 int /*<<< orphan*/  file_list_get_at_offset (int /*<<< orphan*/ ,unsigned int,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_pathname_application_special (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_pathname_base_noext (char*,char const*,int) ; 
 int /*<<< orphan*/  fill_pathname_join_concat (char*,char*,char*,char*,int) ; 
 int /*<<< orphan*/  fill_pathname_join_delim (char*,char*,char*,char,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  image_texture_free (struct texture_image*) ; 
 scalar_t__ image_texture_load (struct texture_image*,char*) ; 
 scalar_t__ malloc (int) ; 
 TYPE_1__* stripes_get_userdata_from_horizontal_list (TYPE_2__*,unsigned int) ; 
 size_t stripes_list_get_size (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* stripes_node_allocate_userdata (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  stripes_toggle_horizontal_list (TYPE_2__*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strstr (char const*,char*) ; 
 int /*<<< orphan*/  video_driver_supports_rgba () ; 
 int /*<<< orphan*/  video_driver_texture_load (struct texture_image*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_driver_texture_unload (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stripes_context_reset_horizontal_list(
      stripes_handle_t *stripes)
{
   unsigned i;
   int depth; /* keep this integer */
   size_t list_size                =
      stripes_list_get_size(stripes, MENU_LIST_HORIZONTAL);

   stripes->categories_x_pos           =
      stripes->categories_passive_width *
      -(float)stripes->categories_selection_ptr;

   depth                           = (stripes->depth > 1) ? 2 : 1;
   stripes->x                          = stripes->icon_size * -(depth*2-2);

   for (i = 0; i < list_size; i++)
   {
      const char *path                          = NULL;
      stripes_node_t *node                          =
         stripes_get_userdata_from_horizontal_list(stripes, i);

      if (!node)
      {
         node = stripes_node_allocate_userdata(stripes, i);
         if (!node)
            continue;
      }

      file_list_get_at_offset(stripes->horizontal_list, i,
            &path, NULL, NULL, NULL);

      if (!path)
         continue;

      if (!strstr(path, ".lpl"))
         continue;

      {
         struct texture_image ti;
         char sysname[256];
         char *iconpath            = (char*)
            malloc(PATH_MAX_LENGTH * sizeof(char));
         char *texturepath         = (char*)
            malloc(PATH_MAX_LENGTH * sizeof(char));
         char *content_texturepath = (char*)
            malloc(PATH_MAX_LENGTH * sizeof(char));

         iconpath[0]    = sysname[0] =
         texturepath[0] = content_texturepath[0] = '\0';

         fill_pathname_base_noext(sysname, path, sizeof(sysname));

         fill_pathname_application_special(iconpath,
               PATH_MAX_LENGTH * sizeof(char),
               APPLICATION_SPECIAL_DIRECTORY_ASSETS_XMB_ICONS);

         fill_pathname_join_concat(texturepath, iconpath, sysname,
               ".png",
               PATH_MAX_LENGTH * sizeof(char));

         ti.width         = 0;
         ti.height        = 0;
         ti.pixels        = NULL;
         ti.supports_rgba = video_driver_supports_rgba();

         if (image_texture_load(&ti, texturepath))
         {
            if (ti.pixels)
            {
               video_driver_texture_unload(&node->icon);
               video_driver_texture_load(&ti,
                     TEXTURE_FILTER_MIPMAP_LINEAR, &node->icon);
            }

            image_texture_free(&ti);
         }

         strlcat(iconpath, sysname, PATH_MAX_LENGTH * sizeof(char));
         fill_pathname_join_delim(content_texturepath, iconpath,
               "content.png", '-',
               PATH_MAX_LENGTH * sizeof(char));

         if (image_texture_load(&ti, content_texturepath))
         {
            if (ti.pixels)
            {
               video_driver_texture_unload(&node->content_icon);
               video_driver_texture_load(&ti,
                     TEXTURE_FILTER_MIPMAP_LINEAR, &node->content_icon);
            }

            image_texture_free(&ti);
         }

         free(iconpath);
         free(texturepath);
         free(content_texturepath);
      }
   }

   stripes_toggle_horizontal_list(stripes);
}