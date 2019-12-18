#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  url ;
typedef  int /*<<< orphan*/  retro_task_t ;
struct TYPE_6__ {int /*<<< orphan*/ * http_task; scalar_t__ overwrite; } ;
typedef  TYPE_1__ pl_thumb_handle_t ;
typedef  int /*<<< orphan*/  path ;
struct TYPE_7__ {int /*<<< orphan*/  path; int /*<<< orphan*/  enum_idx; } ;
typedef  TYPE_2__ file_transfer_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENUM_LABEL_CB_SINGLE_THUMBNAIL ; 
 int PATH_MAX_LENGTH ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  cb_generic_download ; 
 scalar_t__ get_thumbnail_paths (TYPE_1__*,char*,int,char*,int) ; 
 int /*<<< orphan*/  path_is_valid (char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ task_push_http_transfer (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void download_pl_thumbnail(pl_thumb_handle_t *pl_thumb)
{
   char path[PATH_MAX_LENGTH];
   char url[2048];
   
   path[0] = '\0';
   url[0] = '\0';
   
   /* Check if paths are valid */
   if (get_thumbnail_paths(pl_thumb, path, sizeof(path), url, sizeof(url)))
   {
      /* Only download missing thumbnails */
      if (!path_is_valid(path) || pl_thumb->overwrite)
      {
         file_transfer_t *transf = (file_transfer_t*)calloc(1, sizeof(file_transfer_t));
         if (!transf)
            return; /* If this happens then everything is broken anyway... */
         
         /* Initialise file transfer */
         transf->enum_idx = MENU_ENUM_LABEL_CB_SINGLE_THUMBNAIL;
         strlcpy(transf->path, path, sizeof(transf->path));
         
         /* Note: We don't actually care if this fails since that
          * just means the file is missing from the server, so it's
          * not something we can handle here... */
         pl_thumb->http_task = (retro_task_t*)task_push_http_transfer(url, true, NULL, cb_generic_download, transf);
      }
   }
}