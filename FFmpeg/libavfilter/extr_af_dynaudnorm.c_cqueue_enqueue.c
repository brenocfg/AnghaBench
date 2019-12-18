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
struct TYPE_3__ {int nb_elements; int size; int first; double* elements; } ;
typedef  TYPE_1__ cqueue ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert2 (int) ; 

__attribute__((used)) static int cqueue_enqueue(cqueue *q, double element)
{
    int i;

    av_assert2(q->nb_elements != q->size);

    i = (q->first + q->nb_elements) % q->size;
    q->elements[i] = element;
    q->nb_elements++;

    return 0;
}