#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_5__ {int x; int y; int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ cavs_vector ;
struct TYPE_6__ {int* scale_den; } ;
typedef  TYPE_2__ AVSContext ;

/* Variables and functions */
 size_t FFMAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FF_SIGNBIT (int) ; 

__attribute__((used)) static inline void scale_mv(AVSContext *h, int *d_x, int *d_y,
                            cavs_vector *src, int distp)
{
    int64_t den = h->scale_den[FFMAX(src->ref, 0)];
    *d_x = (src->x * distp * den + 256 + FF_SIGNBIT(src->x)) >> 9;
    *d_y = (src->y * distp * den + 256 + FF_SIGNBIT(src->y)) >> 9;
}