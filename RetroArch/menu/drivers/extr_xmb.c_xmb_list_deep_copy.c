#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xmb_node_t ;
struct item_file {int /*<<< orphan*/ * label; int /*<<< orphan*/ * path; int /*<<< orphan*/ * alt; void* actiondata; void* userdata; } ;
typedef  int /*<<< orphan*/  menu_file_list_cbs_t ;
typedef  uintptr_t menu_animation_ctx_tag ;
struct TYPE_9__ {size_t size; struct item_file* list; } ;
typedef  TYPE_1__ file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  file_list_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  file_list_reserve (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  file_list_set_actiondata (TYPE_1__*,size_t,void*) ; 
 int /*<<< orphan*/  file_list_set_userdata (TYPE_1__*,size_t,void*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  menu_animation_kill_by_tag (uintptr_t*) ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ *) ; 
 scalar_t__ string_is_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ xmb_copy_node (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xmb_free_list_nodes (TYPE_1__*,int) ; 

__attribute__((used)) static void xmb_list_deep_copy(const file_list_t *src, file_list_t *dst,
      size_t first, size_t last)
{
   size_t i, j = 0;
   menu_animation_ctx_tag tag = (uintptr_t)dst;

   menu_animation_kill_by_tag(&tag);

   xmb_free_list_nodes(dst, true);

   file_list_clear(dst);
   file_list_reserve(dst, (last + 1) - first);

   for (i = first; i <= last; ++i)
   {
      struct item_file *d = &dst->list[j];
      struct item_file *s = &src->list[i];

      void *src_udata = s->userdata;
      void *src_adata = s->actiondata;

      *d       = *s;
      d->alt   = string_is_empty(d->alt)   ? NULL : strdup(d->alt);
      d->path  = string_is_empty(d->path)  ? NULL : strdup(d->path);
      d->label = string_is_empty(d->label) ? NULL : strdup(d->label);

      if (src_udata)
         file_list_set_userdata(dst, j, (void*)xmb_copy_node((const xmb_node_t*)src_udata));

      if (src_adata)
      {
         void *data = malloc(sizeof(menu_file_list_cbs_t));
         memcpy(data, src_adata, sizeof(menu_file_list_cbs_t));
         file_list_set_actiondata(dst, j, data);
      }

      ++j;
   }

   dst->size = j;
}