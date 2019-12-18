#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int size; int /*<<< orphan*/  elements; scalar_t__ first; scalar_t__ nb_elements; } ;
typedef  TYPE_1__ cqueue ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 TYPE_1__* av_malloc (int) ; 
 int /*<<< orphan*/  av_malloc_array (int,int) ; 

__attribute__((used)) static cqueue *cqueue_create(int size)
{
    cqueue *q;

    q = av_malloc(sizeof(cqueue));
    if (!q)
        return NULL;

    q->size = size;
    q->nb_elements = 0;
    q->first = 0;

    q->elements = av_malloc_array(size, sizeof(double));
    if (!q->elements) {
        av_free(q);
        return NULL;
    }

    return q;
}