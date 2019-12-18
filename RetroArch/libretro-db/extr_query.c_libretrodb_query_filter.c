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
struct TYPE_2__ {scalar_t__ bool_; } ;
struct rmsgpack_dom_value {scalar_t__ type; TYPE_1__ val; } ;
struct invocation {int /*<<< orphan*/  argv; int /*<<< orphan*/  argc; struct rmsgpack_dom_value (* func ) (struct rmsgpack_dom_value,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct query {struct invocation root; } ;
typedef  int /*<<< orphan*/  libretrodb_query_t ;

/* Variables and functions */
 scalar_t__ RDT_BOOL ; 
 struct rmsgpack_dom_value stub1 (struct rmsgpack_dom_value,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int libretrodb_query_filter(libretrodb_query_t *q,
      struct rmsgpack_dom_value *v)
{
   struct invocation inv = ((struct query *)q)->root;
   struct rmsgpack_dom_value res = inv.func(*v, inv.argc, inv.argv);
   return (res.type == RDT_BOOL && res.val.bool_);
}