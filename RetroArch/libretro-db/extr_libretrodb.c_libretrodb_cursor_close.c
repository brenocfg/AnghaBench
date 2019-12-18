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
struct TYPE_3__ {int eof; int /*<<< orphan*/ * query; int /*<<< orphan*/ * db; int /*<<< orphan*/ * fd; scalar_t__ is_valid; } ;
typedef  TYPE_1__ libretrodb_cursor_t ;

/* Variables and functions */
 int /*<<< orphan*/  filestream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libretrodb_query_free (int /*<<< orphan*/ *) ; 

void libretrodb_cursor_close(libretrodb_cursor_t *cursor)
{
   if (!cursor)
      return;

   if (cursor->fd)
      filestream_close(cursor->fd);

   if (cursor->query)
      libretrodb_query_free(cursor->query);

   cursor->is_valid = 0;
   cursor->eof      = 1;
   cursor->fd       = NULL;
   cursor->db       = NULL;
   cursor->query    = NULL;
}