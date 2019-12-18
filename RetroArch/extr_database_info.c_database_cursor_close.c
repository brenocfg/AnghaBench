#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  libretrodb_t ;
typedef  int /*<<< orphan*/  libretrodb_cursor_t ;

/* Variables and functions */
 int /*<<< orphan*/  libretrodb_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libretrodb_cursor_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int database_cursor_close(libretrodb_t *db, libretrodb_cursor_t *cur)
{
   libretrodb_cursor_close(cur);
   libretrodb_close(db);

   return 0;
}