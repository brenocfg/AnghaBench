#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  buckets; TYPE_3__ buckets_buffer; } ;
typedef  TYPE_1__ HashIndex ;

/* Variables and functions */
 int /*<<< orphan*/  PyBuffer_Release (TYPE_3__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hashindex_free_buckets(HashIndex *index)
{
#ifndef BORG_NO_PYTHON
    if(index->buckets_buffer.buf) {
        PyBuffer_Release(&index->buckets_buffer);
    } else
#endif
    {
        free(index->buckets);
    }
}