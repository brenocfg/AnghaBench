#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
union string_list_elem_attr {int /*<<< orphan*/  member_0; } ;
struct utsname {int /*<<< orphan*/  release; } ;
struct string_list {unsigned int size; TYPE_1__* elems; } ;
struct TYPE_10__ {int fd; int flags; struct TYPE_10__* data; int /*<<< orphan*/  path_list; TYPE_4__* wd_list; } ;
typedef  TYPE_2__ path_change_data_t ;
typedef  TYPE_2__ inotify_data_t ;
struct TYPE_11__ {unsigned int count; int /*<<< orphan*/ * data; } ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int IN_CLOSE_WRITE ; 
 int IN_DELETE_SELF ; 
 int IN_MODIFY ; 
 int IN_MOVE_SELF ; 
 int O_NONBLOCK ; 
 int PATH_CHANGE_TYPE_FILE_DELETED ; 
 int PATH_CHANGE_TYPE_FILE_MOVED ; 
 int PATH_CHANGE_TYPE_MODIFIED ; 
 int PATH_CHANGE_TYPE_WRITE_FILE_CLOSED ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RARCH_WARN (char*,...) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int inotify_add_watch (int,int /*<<< orphan*/ ,int) ; 
 int inotify_init () ; 
 int /*<<< orphan*/  inotify_rm_watch (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_vector_list_append (TYPE_4__*,int) ; 
 int /*<<< orphan*/  int_vector_list_free (TYPE_4__*) ; 
 TYPE_4__* int_vector_list_new () ; 
 int /*<<< orphan*/  sscanf (int /*<<< orphan*/ ,char*,int*,int*,unsigned int*) ; 
 int /*<<< orphan*/  string_list_append (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union string_list_elem_attr) ; 
 int /*<<< orphan*/  string_list_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_new () ; 
 scalar_t__ uname (struct utsname*) ; 

__attribute__((used)) static void frontend_unix_watch_path_for_changes(struct string_list *list, int flags, path_change_data_t **change_data)
{
#ifdef HAS_INOTIFY
   int major = 0;
   int minor = 0;
   int inotify_mask = 0, fd = 0;
   unsigned i, krel = 0;
   struct utsname buffer;
   inotify_data_t *inotify_data;

   if (!list)
   {
      if (change_data && *change_data)
      {
         /* free the original data */
         inotify_data = (inotify_data_t*)((*change_data)->data);

         if (inotify_data->wd_list->count > 0)
         {
            for (i = 0; i < inotify_data->wd_list->count; i++)
            {
               inotify_rm_watch(inotify_data->fd, inotify_data->wd_list->data[i]);
            }
         }

         int_vector_list_free(inotify_data->wd_list);
         string_list_free(inotify_data->path_list);
         close(inotify_data->fd);
         free(inotify_data);
         free(*change_data);
         return;
      }
      else
         return;
   }
   else if (list->size == 0)
      return;
   else
      if (!change_data)
         return;

   if (uname(&buffer) != 0)
   {
      RARCH_WARN("watch_path_for_changes: Failed to get current kernel version.\n");
      return;
   }

   /* get_os doesn't provide all three */
   sscanf(buffer.release, "%d.%d.%u", &major, &minor, &krel);

   /* check if we are actually running on a high enough kernel version as well */
   if (major < 2)
   {
      RARCH_WARN("watch_path_for_changes: inotify unsupported on this kernel version (%d.%d.%u).\n", major, minor, krel);
      return;
   }
   else if (major == 2)
   {
      if (minor < 6)
      {
         RARCH_WARN("watch_path_for_changes: inotify unsupported on this kernel version (%d.%d.%u).\n", major, minor, krel);
         return;
      }
      else if (minor == 6)
      {
         if (krel < 13)
         {
            RARCH_WARN("watch_path_for_changes: inotify unsupported on this kernel version (%d.%d.%u).\n", major, minor, krel);
            return;
         }
         else
         {
            /* anything >= 2.6.13 is supported */
         }
      }
      else
      {
         /* anything >= 2.7 is supported */
      }
   }
   else
   {
      /* anything >= 3 is supported */
   }

   fd = inotify_init();

   if (fd < 0)
   {
      RARCH_WARN("watch_path_for_changes: Could not initialize inotify.\n");
      return;
   }

   if (fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK))
   {
      RARCH_WARN("watch_path_for_changes: Could not set socket to non-blocking.\n");
      return;
   }

   inotify_data = (inotify_data_t*)calloc(1, sizeof(*inotify_data));
   inotify_data->fd = fd;

   inotify_data->wd_list = int_vector_list_new();
   inotify_data->path_list = string_list_new();

   /* handle other flags here as new ones are added */
   if (flags & PATH_CHANGE_TYPE_MODIFIED)
      inotify_mask |= IN_MODIFY;
   if (flags & PATH_CHANGE_TYPE_WRITE_FILE_CLOSED)
      inotify_mask |= IN_CLOSE_WRITE;
   if (flags & PATH_CHANGE_TYPE_FILE_MOVED)
      inotify_mask |= IN_MOVE_SELF;
   if (flags & PATH_CHANGE_TYPE_FILE_DELETED)
      inotify_mask |= IN_DELETE_SELF;

   inotify_data->flags = inotify_mask;

   for (i = 0; i < list->size; i++)
   {
      int wd = inotify_add_watch(fd, list->elems[i].data, inotify_mask);
      union string_list_elem_attr attr = {0};

      RARCH_LOG("Watching file for changes: %s\n", list->elems[i].data);

      int_vector_list_append(inotify_data->wd_list, wd);
      string_list_append(inotify_data->path_list, list->elems[i].data, attr);
   }

   *change_data = (path_change_data_t*)calloc(1, sizeof(path_change_data_t));
   (*change_data)->data = inotify_data;
#endif
}