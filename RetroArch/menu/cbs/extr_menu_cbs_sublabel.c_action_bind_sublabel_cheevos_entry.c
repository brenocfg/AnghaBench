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
struct TYPE_3__ {unsigned int idx; char* s; size_t len; } ;
typedef  TYPE_1__ rcheevos_ctx_desc_t ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 unsigned int MENU_SETTINGS_CHEEVOS_START ; 
 int MENU_SUBLABEL_MAX_LENGTH ; 
 int /*<<< orphan*/  rcheevos_get_description (TYPE_1__*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static int action_bind_sublabel_cheevos_entry(
      file_list_t *list,
      unsigned type, unsigned i,
      const char *label, const char *path,
      char *s, size_t len)
{
#ifdef HAVE_CHEEVOS
   rcheevos_ctx_desc_t desc_info;
   unsigned new_id;
   char fetched_sublabel[MENU_SUBLABEL_MAX_LENGTH];

   fetched_sublabel[0] = '\0';

   new_id              = type - MENU_SETTINGS_CHEEVOS_START;
   desc_info.idx       = new_id;
   desc_info.s         = fetched_sublabel;
   desc_info.len       = len;

   rcheevos_get_description((rcheevos_ctx_desc_t*) &desc_info);

   strlcpy(s, desc_info.s, len);
#endif
   return 0;
}