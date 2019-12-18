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
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_3__ {int elt_size; int nalloc; scalar_t__ nelts; int /*<<< orphan*/ * pool; int /*<<< orphan*/  elts; } ;
typedef  TYPE_1__ apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pcalloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void make_array_core(apr_array_header_t *res, apr_pool_t *p,
			    int nelts, int elt_size, int clear)
{
    /*
     * Assure sanity if someone asks for
     * array of zero elts.
     */
    if (nelts < 1) {
        nelts = 1;
    }

    if (clear) {
        res->elts = apr_pcalloc(p, nelts * elt_size);
    }
    else {
        res->elts = apr_palloc(p, nelts * elt_size);
    }

    res->pool = p;
    res->elt_size = elt_size;
    res->nelts = 0;		/* No active elements yet... */
    res->nalloc = nelts;	/* ...but this many allocated */
}