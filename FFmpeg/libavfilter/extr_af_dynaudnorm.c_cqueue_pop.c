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
struct TYPE_4__ {int first; int size; int /*<<< orphan*/  nb_elements; } ;
typedef  TYPE_1__ cqueue ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert2 (int) ; 
 int /*<<< orphan*/  cqueue_empty (TYPE_1__*) ; 

__attribute__((used)) static int cqueue_pop(cqueue *q)
{
    av_assert2(!cqueue_empty(q));

    q->first = (q->first + 1) % q->size;
    q->nb_elements--;

    return 0;
}