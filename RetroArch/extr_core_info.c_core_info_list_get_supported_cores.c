#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct string_list {int dummy; } ;
typedef  int /*<<< orphan*/  core_info_t ;
struct TYPE_3__ {size_t count; int /*<<< orphan*/ * list; } ;
typedef  TYPE_1__ core_info_list_t ;

/* Variables and functions */
 scalar_t__ core_info_does_support_any_file (int /*<<< orphan*/  const*,struct string_list*) ; 
 scalar_t__ core_info_does_support_file (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/  core_info_qsort_cmp ; 
 struct string_list* core_info_tmp_list ; 
 char const* core_info_tmp_path ; 
 struct string_list* file_archive_get_file_list (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ path_is_compressed_file (char const*) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 

void core_info_list_get_supported_cores(core_info_list_t *core_info_list,
      const char *path, const core_info_t **infos, size_t *num_infos)
{
   size_t i;
   size_t supported         = 0;
#ifdef HAVE_COMPRESSION
   struct string_list *list = NULL;
#endif

   if (!core_info_list)
      return;

   core_info_tmp_path = path;

#ifdef HAVE_COMPRESSION
   if (path_is_compressed_file(path))
      list = file_archive_get_file_list(path, NULL);
   core_info_tmp_list = list;
#endif

   /* Let supported core come first in list so we can return
    * a pointer to them. */
   qsort(core_info_list->list, core_info_list->count,
         sizeof(core_info_t), core_info_qsort_cmp);

   for (i = 0; i < core_info_list->count; i++, supported++)
   {
      const core_info_t *core = &core_info_list->list[i];

      if (core_info_does_support_file(core, path))
         continue;

#ifdef HAVE_COMPRESSION
      if (core_info_does_support_any_file(core, list))
         continue;
#endif

      break;
   }

#ifdef HAVE_COMPRESSION
   if (list)
      string_list_free(list);
#endif

   *infos     = core_info_list->list;
   *num_infos = supported;
}