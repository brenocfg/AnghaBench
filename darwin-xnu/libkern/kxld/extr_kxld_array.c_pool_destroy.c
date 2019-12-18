#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ buffer; } ;
typedef  TYPE_1__ KXLDArrayPool ;

/* Variables and functions */
 int /*<<< orphan*/  kxld_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  kxld_page_free (scalar_t__,size_t) ; 

__attribute__((used)) static void
pool_destroy(KXLDArrayPool *pool, size_t capacity)
{
    if (pool) {
        if (pool->buffer) kxld_page_free(pool->buffer, capacity);
        kxld_free(pool, sizeof(*pool));
    }
}