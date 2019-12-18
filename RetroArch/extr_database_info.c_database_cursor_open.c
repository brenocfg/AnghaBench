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
typedef  int /*<<< orphan*/  libretrodb_query_t ;
typedef  int /*<<< orphan*/  libretrodb_cursor_t ;

/* Variables and functions */
 int /*<<< orphan*/  libretrodb_close (int /*<<< orphan*/ *) ; 
 scalar_t__ libretrodb_cursor_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ libretrodb_open (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ libretrodb_query_compile (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  libretrodb_query_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int database_cursor_open(libretrodb_t *db,
      libretrodb_cursor_t *cur, const char *path, const char *query)
{
   const char *error     = NULL;
   libretrodb_query_t *q = NULL;

   if ((libretrodb_open(path, db)) != 0)
      return -1;

   if (query)
      q = (libretrodb_query_t*)libretrodb_query_compile(db, query,
      strlen(query), &error);

   if (error)
      goto error;
   if ((libretrodb_cursor_open(db, cur, q)) != 0)
      goto error;

   if (q)
      libretrodb_query_free(q);

   return 0;

error:
   if (q)
      libretrodb_query_free(q);
   libretrodb_close(db);

   return -1;
}