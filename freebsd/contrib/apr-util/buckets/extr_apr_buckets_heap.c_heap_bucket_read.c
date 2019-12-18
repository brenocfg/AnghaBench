#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_read_type_e ;
struct TYPE_4__ {char* base; } ;
typedef  TYPE_1__ apr_bucket_heap ;
struct TYPE_5__ {int start; int /*<<< orphan*/  length; TYPE_1__* data; } ;
typedef  TYPE_2__ apr_bucket ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 

__attribute__((used)) static apr_status_t heap_bucket_read(apr_bucket *b, const char **str, 
                                     apr_size_t *len, apr_read_type_e block)
{
    apr_bucket_heap *h = b->data;

    *str = h->base + b->start;
    *len = b->length;
    return APR_SUCCESS;
}