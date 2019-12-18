#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct inotify_event {int mask; scalar_t__ wd; scalar_t__ len; } ;
struct TYPE_10__ {scalar_t__ data; } ;
typedef  TYPE_4__ path_change_data_t ;
struct TYPE_11__ {int flags; TYPE_3__* path_list; TYPE_1__* wd_list; int /*<<< orphan*/  fd; } ;
typedef  TYPE_5__ inotify_data_t ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_9__ {TYPE_2__* elems; } ;
struct TYPE_8__ {char* data; } ;
struct TYPE_7__ {unsigned int count; scalar_t__* data; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int INOTIFY_BUF_LEN ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 scalar_t__ fopen_utf8 (char const*,char*) ; 
 int /*<<< orphan*/  fsync (int /*<<< orphan*/ ) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool frontend_unix_check_for_path_changes(path_change_data_t *change_data)
{
#ifdef HAS_INOTIFY
   inotify_data_t *inotify_data = (inotify_data_t*)(change_data->data);
   char buffer[INOTIFY_BUF_LEN] = {0};
   int length, i = 0;

   while ((length = read(inotify_data->fd, buffer, INOTIFY_BUF_LEN)) > 0)
   {
      i = 0;

      while (i < length && i < sizeof(buffer))
      {
         struct inotify_event *event = (struct inotify_event *)&buffer[i];

         if (event->mask & inotify_data->flags)
         {
            unsigned j;

            /* A successful close does not guarantee that the
             * data has been successfully saved to disk,
             * as the kernel defers writes. It is
             * not common for a file system to flush
             * the buffers when the stream is closed.
             *
             * So we manually fsync() here to flush the data
             * to disk, to make sure that the new data is
             * immediately available when the file is re-read.
             */
            for (j = 0; j < inotify_data->wd_list->count; j++)
            {
               if (inotify_data->wd_list->data[j] == event->wd)
               {
                  /* found the right file, now sync it */
                  const char *path = inotify_data->path_list->elems[j].data;
                  FILE         *fp = (FILE*)fopen_utf8(path, "rb");

                  RARCH_LOG("file change detected: %s\n", path);

                  if (fp)
                  {
                     fsync(fileno(fp));
                     fclose(fp);
                  }
               }
            }

            return true;
         }

         i += sizeof(struct inotify_event) + event->len;
      }
   }
#endif
   return false;
}