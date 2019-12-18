#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int argc; struct query* argv; } ;
struct query {scalar_t__ ref_count; TYPE_1__ root; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct query*) ; 
 int /*<<< orphan*/  query_argument_free (struct query*) ; 

void libretrodb_query_free(void *q)
{
   unsigned i;
   struct query *real_q = (struct query*)q;

   real_q->ref_count--;
   if (real_q->ref_count > 0)
      return;

   for (i = 0; i < real_q->root.argc; i++)
      query_argument_free(&real_q->root.argv[i]);

   free(real_q->root.argv);
   real_q->root.argv = NULL;
   real_q->root.argc = 0;
   free(real_q);
}