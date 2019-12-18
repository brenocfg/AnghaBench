#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* buffer; } ;
typedef  TYPE_1__ KXLDArrayPool ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  finish ; 
 TYPE_1__* kxld_alloc (int) ; 
 TYPE_1__* kxld_page_alloc (size_t) ; 
 int /*<<< orphan*/  pool_destroy (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  require (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static KXLDArrayPool *
pool_create(size_t capacity)
{
    KXLDArrayPool *pool = NULL, *rval = NULL;

    pool = kxld_alloc(sizeof(*pool));
    require(pool, finish);

    pool->buffer = kxld_page_alloc(capacity);
    require(pool->buffer, finish);
    bzero(pool->buffer, capacity);

    rval = pool;
    pool = NULL;

finish:
    if (pool) pool_destroy(pool, capacity);
    return rval;
}