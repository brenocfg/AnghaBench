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
typedef  int /*<<< orphan*/  cqueue ;

/* Variables and functions */
 double DBL_MAX ; 
 double FFMIN (double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cqueue_peek (int /*<<< orphan*/ *,int) ; 
 int cqueue_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static double minimum_filter(cqueue *q)
{
    double min = DBL_MAX;
    int i;

    for (i = 0; i < cqueue_size(q); i++) {
        min = FFMIN(min, cqueue_peek(q, i));
    }

    return min;
}