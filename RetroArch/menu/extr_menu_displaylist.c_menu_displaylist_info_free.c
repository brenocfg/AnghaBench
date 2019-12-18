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
struct TYPE_3__ {int /*<<< orphan*/ * path; int /*<<< orphan*/ * label; int /*<<< orphan*/ * path_c; int /*<<< orphan*/ * path_b; int /*<<< orphan*/ * exts; } ;
typedef  TYPE_1__ menu_displaylist_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void menu_displaylist_info_free(menu_displaylist_info_t *info)
{
   if (!info)
      return;
   if (info->exts)
      free(info->exts);
   if (info->path_b)
      free(info->path_b);
   if (info->path_c)
      free(info->path_c);
   if (info->label)
      free(info->label);
   if (info->path)
      free(info->path);
   info->exts   = NULL;
   info->path_b = NULL;
   info->path_c = NULL;
   info->label  = NULL;
   info->path   = NULL;
}