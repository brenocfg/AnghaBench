#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  libretrodb_header_t ;
struct TYPE_5__ {TYPE_1__* db; int /*<<< orphan*/  fd; scalar_t__ eof; } ;
typedef  TYPE_2__ libretrodb_cursor_t ;
struct TYPE_4__ {scalar_t__ root; } ;

/* Variables and functions */
 int /*<<< orphan*/  RETRO_VFS_SEEK_POSITION_START ; 
 scalar_t__ filestream_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int libretrodb_cursor_reset(libretrodb_cursor_t *cursor)
{
   cursor->eof = 0;
   return (int)filestream_seek(cursor->fd,
         (ssize_t)(cursor->db->root + sizeof(libretrodb_header_t)),
         RETRO_VFS_SEEK_POSITION_START);
}