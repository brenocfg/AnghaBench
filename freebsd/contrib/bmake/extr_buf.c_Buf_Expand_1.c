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
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  bmake_realloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ max (int /*<<< orphan*/ ,int) ; 

void
Buf_Expand_1(Buffer *bp)
{
    bp->size += max(bp->size, 16);
    bp->buffer = bmake_realloc(bp->buffer, bp->size);
}