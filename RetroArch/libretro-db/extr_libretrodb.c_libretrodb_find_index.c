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
typedef  scalar_t__ ssize_t ;
struct TYPE_6__ {int /*<<< orphan*/  fd; scalar_t__ first_index_offset; } ;
typedef  TYPE_1__ libretrodb_t ;
struct TYPE_7__ {scalar_t__ next; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ libretrodb_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  RETRO_VFS_SEEK_POSITION_CURRENT ; 
 int /*<<< orphan*/  RETRO_VFS_SEEK_POSITION_START ; 
 scalar_t__ filestream_get_size (int /*<<< orphan*/ ) ; 
 scalar_t__ filestream_seek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ filestream_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libretrodb_read_index_header (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int libretrodb_find_index(libretrodb_t *db, const char *index_name,
      libretrodb_index_t *idx)
{
   ssize_t eof    = filestream_get_size(db->fd);
   ssize_t offset = filestream_seek(db->fd,
         (ssize_t)db->first_index_offset,
         RETRO_VFS_SEEK_POSITION_START);

   /* TODO: this should use filestream_eof instead */
   while (offset < eof)
   {
      libretrodb_read_index_header(db->fd, idx);

      if (strncmp(index_name, idx->name, strlen(idx->name)) == 0)
         return 0;

      filestream_seek(db->fd, (ssize_t)idx->next,
            RETRO_VFS_SEEK_POSITION_CURRENT);
      offset = filestream_tell(db->fd);
   }

   return -1;
}