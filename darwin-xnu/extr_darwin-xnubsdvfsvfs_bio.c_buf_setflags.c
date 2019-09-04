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
typedef  int int32_t ;
typedef  TYPE_1__* buf_t ;
struct TYPE_3__ {int /*<<< orphan*/  b_flags; } ;

/* Variables and functions */
 int BUF_X_WRFLAGS ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int) ; 

void
buf_setflags(buf_t bp, int32_t flags) {

        SET(bp->b_flags, (flags & BUF_X_WRFLAGS));
}