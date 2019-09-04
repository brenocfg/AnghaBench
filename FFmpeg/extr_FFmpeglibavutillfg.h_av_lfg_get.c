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
struct TYPE_3__ {unsigned int* state; int index; } ;
typedef  TYPE_1__ AVLFG ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int av_lfg_get(AVLFG *c){
    c->state[c->index & 63] = c->state[(c->index-24) & 63] + c->state[(c->index-55) & 63];
    return c->state[c->index++ & 63];
}