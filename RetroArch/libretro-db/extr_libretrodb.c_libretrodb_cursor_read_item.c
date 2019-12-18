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
struct rmsgpack_dom_value {scalar_t__ type; } ;
struct TYPE_3__ {int eof; scalar_t__ query; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ libretrodb_cursor_t ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ RDT_NULL ; 
 int /*<<< orphan*/  libretrodb_query_filter (scalar_t__,struct rmsgpack_dom_value*) ; 
 int rmsgpack_dom_read (int /*<<< orphan*/ ,struct rmsgpack_dom_value*) ; 
 int /*<<< orphan*/  rmsgpack_dom_value_free (struct rmsgpack_dom_value*) ; 

int libretrodb_cursor_read_item(libretrodb_cursor_t *cursor,
      struct rmsgpack_dom_value *out)
{
   int rv;

   if (cursor->eof)
      return EOF;

retry:
   rv = rmsgpack_dom_read(cursor->fd, out);
   if (rv < 0)
      return rv;

   if (out->type == RDT_NULL)
   {
      cursor->eof = 1;
      return EOF;
   }

   if (cursor->query)
   {
      if (!libretrodb_query_filter(cursor->query, out))
      {
         rmsgpack_dom_value_free(out);
         goto retry;
      }
   }

   return 0;
}