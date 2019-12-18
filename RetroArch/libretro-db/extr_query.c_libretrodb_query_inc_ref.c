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
struct query {int ref_count; } ;
typedef  int /*<<< orphan*/  libretrodb_query_t ;

/* Variables and functions */

void libretrodb_query_inc_ref(libretrodb_query_t *q)
{
   struct query *rq = (struct query*)q;
   if (rq)
      rq->ref_count += 1;
}