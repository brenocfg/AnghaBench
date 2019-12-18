#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct string_list {int dummy; } ;
typedef  int /*<<< orphan*/  softfilter_simd_mask_t ;
struct TYPE_6__ {int /*<<< orphan*/  conf; } ;
typedef  TYPE_1__ rarch_softfilter_t ;
typedef  int /*<<< orphan*/  ext_name ;
typedef  enum retro_pixel_format { ____Placeholder_retro_pixel_format } retro_pixel_format ;
typedef  int /*<<< orphan*/  basedir ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_ERR (char*,...) ; 
 int /*<<< orphan*/  append_softfilter_plugs (TYPE_1__*,struct string_list*) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  config_file_new_from_path_to_string (char const*) ; 
 int /*<<< orphan*/  cpu_features_get () ; 
 int /*<<< orphan*/  create_softfilter_graph (TYPE_1__*,int,unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 struct string_list* dir_list_new (char*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  fill_pathname_basedir (char*,char const*,int) ; 
 int /*<<< orphan*/  frontend_driver_get_core_extension (char*,int) ; 
 int /*<<< orphan*/  rarch_softfilter_free (TYPE_1__*) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 

rarch_softfilter_t *rarch_softfilter_new(const char *filter_config,
      unsigned threads,
      enum retro_pixel_format in_pixel_format,
      unsigned max_width, unsigned max_height)
{
   softfilter_simd_mask_t cpu_features = (softfilter_simd_mask_t)cpu_features_get();
   char basedir[PATH_MAX_LENGTH];
#ifdef HAVE_DYLIB
   char ext_name[PATH_MAX_LENGTH];
#endif
   struct string_list *plugs     = NULL;
   rarch_softfilter_t *filt      = NULL;

   (void)basedir;

   filt = (rarch_softfilter_t*)calloc(1, sizeof(*filt));
   if (!filt)
      return NULL;

   if (!(filt->conf = config_file_new_from_path_to_string(filter_config)))
   {
      RARCH_ERR("[SoftFilter]: Did not find config: %s\n", filter_config);
      goto error;
   }

#if defined(HAVE_DYLIB)
   fill_pathname_basedir(basedir, filter_config, sizeof(basedir));

   if (!frontend_driver_get_core_extension(ext_name, sizeof(ext_name)))
         goto error;

   plugs = dir_list_new(basedir, ext_name, false, false, false, false);

   if (!plugs)
   {
      RARCH_ERR("[SoftFilter]: Could not build up string list...\n");
      goto error;
   }
#endif
   if (!append_softfilter_plugs(filt, plugs))
   {
      RARCH_ERR("[SoftFitler]: Failed to append softfilter plugins...\n");
      goto error;
   }

   if (plugs)
      string_list_free(plugs);
   plugs = NULL;

   if (!create_softfilter_graph(filt, in_pixel_format,
            max_width, max_height, cpu_features, threads))
   {
      RARCH_ERR("[SoftFitler]: Failed to create softfilter graph...\n");
      goto error;
   }

   return filt;

error:
   if (plugs)
      string_list_free(plugs);
   plugs = NULL;
   rarch_softfilter_free(filt);
   return NULL;
}