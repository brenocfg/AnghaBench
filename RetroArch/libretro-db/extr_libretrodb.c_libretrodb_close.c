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
struct TYPE_3__ {int /*<<< orphan*/ * fd; int /*<<< orphan*/ * path; } ;
typedef  TYPE_1__ libretrodb_t ;

/* Variables and functions */
 int /*<<< orphan*/  filestream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_is_empty (int /*<<< orphan*/ *) ; 

void libretrodb_close(libretrodb_t *db)
{
   if (db->fd)
      filestream_close(db->fd);
   if (!string_is_empty(db->path))
      free(db->path);
   db->path = NULL;
   db->fd   = NULL;
}