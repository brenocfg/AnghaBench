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
struct TYPE_3__ {int stride; scalar_t__** src; scalar_t__** ref; } ;
typedef  TYPE_1__ MotionEstContext ;

/* Variables and functions */

__attribute__((used)) static inline void init_mv4_ref(MotionEstContext *c){
    const int stride= c->stride;

    c->ref[1][0] = c->ref[0][0] + 8;
    c->ref[2][0] = c->ref[0][0] + 8*stride;
    c->ref[3][0] = c->ref[2][0] + 8;
    c->src[1][0] = c->src[0][0] + 8;
    c->src[2][0] = c->src[0][0] + 8*stride;
    c->src[3][0] = c->src[2][0] + 8;
}