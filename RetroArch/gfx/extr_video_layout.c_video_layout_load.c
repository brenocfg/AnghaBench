#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rxml_document_t ;
typedef  int /*<<< orphan*/  respath ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {int /*<<< orphan*/  view_array; int /*<<< orphan*/  base_path; scalar_t__ is_archive; } ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char const*) ; 
 scalar_t__ file_archive_compressed_read (char*,void**,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  fill_pathname_basedir (char*,char const*,int) ; 
 int /*<<< orphan*/  free (void*) ; 
 int load (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ path_is_compressed_file (char const*) ; 
 scalar_t__ realloc (void*,size_t) ; 
 int /*<<< orphan*/  rxml_free_document (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rxml_load_document (char const*) ; 
 int /*<<< orphan*/ * rxml_load_document_string (char*) ; 
 int /*<<< orphan*/  set_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 TYPE_1__* video_layout_state ; 
 int /*<<< orphan*/  video_layout_view_index () ; 
 int /*<<< orphan*/  video_layout_view_select (int /*<<< orphan*/ ) ; 

bool video_layout_load(const char *path)
{
   rxml_document_t *doc;
   bool result;

   if(!path || !strlen(path))
      return true;

   video_layout_state->is_archive = path_is_compressed_file(path);

   doc = NULL;

   if(video_layout_state->is_archive)
   {
      void *buf;
      int64_t len;

      char respath[PATH_MAX_LENGTH];
      strlcpy(respath, path, sizeof(respath));
      strlcat(respath, "#", sizeof(respath));
      set_string(&video_layout_state->base_path, respath);

      strlcat(respath, "default.lay", sizeof(respath));
      if (file_archive_compressed_read(respath, &buf, NULL, &len))
      {
         char *str;
         if ((str = (char*)realloc(buf, (size_t)len + 1)))
         {
            str[(size_t)len] = '\0';
            doc = rxml_load_document_string(str);
            free(str);
         }
         else free(buf);
      }
   }
   else
   {
      char respath[PATH_MAX_LENGTH];
      fill_pathname_basedir(respath, path, sizeof(respath));
      set_string(&video_layout_state->base_path, respath);
      doc = rxml_load_document(path);
   }

   if (!doc)
   {
      RARCH_LOG("video_layout: unable to open file \"%s\"\n", path);
      return false;
   }

   result = load(&video_layout_state->view_array, doc);
   rxml_free_document(doc);

   video_layout_view_select(video_layout_view_index());
   return result;
}