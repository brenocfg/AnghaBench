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
typedef  int int32_t ;
struct TYPE_4__ {int shift; int /*<<< orphan*/  round; } ;
typedef  TYPE_1__ TTAFilter ;

/* Variables and functions */
 int /*<<< orphan*/ * ff_tta_shift_1 ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void ff_tta_filter_init(TTAFilter *c, int32_t shift) {
    memset(c, 0, sizeof(TTAFilter));
    c->shift = shift;
    c->round = ff_tta_shift_1[shift-1];
}