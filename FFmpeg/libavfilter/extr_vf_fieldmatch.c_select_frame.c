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
struct TYPE_3__ {int /*<<< orphan*/ * src; int /*<<< orphan*/ * nxt; int /*<<< orphan*/ * prv; } ;
typedef  TYPE_1__ FieldMatchContext ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int mB ; 
 int mN ; 
 int mP ; 
 int mU ; 

__attribute__((used)) static AVFrame *select_frame(FieldMatchContext *fm, int match)
{
    if      (match == mP || match == mB) return fm->prv;
    else if (match == mN || match == mU) return fm->nxt;
    else  /* match == mC */              return fm->src;
}