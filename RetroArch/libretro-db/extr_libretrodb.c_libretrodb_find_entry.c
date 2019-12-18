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
typedef  scalar_t__ uint64_t ;
struct rmsgpack_dom_value {int dummy; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_6__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ libretrodb_t ;
struct TYPE_7__ {scalar_t__ next; scalar_t__ key_size; } ;
typedef  TYPE_2__ libretrodb_index_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  RETRO_VFS_SEEK_POSITION_START ; 
 int binsearch (void*,void const*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int errno ; 
 scalar_t__ filestream_read (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  filestream_seek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ libretrodb_find_index (TYPE_1__*,char const*,TYPE_2__*) ; 
 void* malloc (scalar_t__) ; 
 int rmsgpack_dom_read (int /*<<< orphan*/ ,struct rmsgpack_dom_value*) ; 

int libretrodb_find_entry(libretrodb_t *db, const char *index_name,
      const void *key, struct rmsgpack_dom_value *out)
{
   libretrodb_index_t idx;
   int rv;
   void *buff;
   uint64_t offset;
   ssize_t bufflen, nread = 0;

   if (libretrodb_find_index(db, index_name, &idx) < 0)
      return -1;

   bufflen = idx.next;
   buff = malloc(bufflen);

   if (!buff)
      return -ENOMEM;

   while (nread < bufflen)
   {
      void *buff_ = (uint64_t *)buff + nread;
      rv = (int)filestream_read(db->fd, buff_, bufflen - nread);

      if (rv <= 0)
      {
         free(buff);
         return -errno;
      }
      nread += rv;
   }

   rv = binsearch(buff, key, db->count, (ssize_t)idx.key_size, &offset);
   free(buff);

   if (rv == 0)
      filestream_seek(db->fd, (ssize_t)offset,
            RETRO_VFS_SEEK_POSITION_START);

   return rmsgpack_dom_read(db->fd, out);
}