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
typedef  int /*<<< orphan*/  cqueue ;
struct TYPE_3__ {double* weights; } ;
typedef  TYPE_1__ DynamicAudioNormalizerContext ;

/* Variables and functions */
 double cqueue_peek (int /*<<< orphan*/ *,int) ; 
 int cqueue_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static double gaussian_filter(DynamicAudioNormalizerContext *s, cqueue *q)
{
    double result = 0.0;
    int i;

    for (i = 0; i < cqueue_size(q); i++) {
        result += cqueue_peek(q, i) * s->weights[i];
    }

    return result;
}