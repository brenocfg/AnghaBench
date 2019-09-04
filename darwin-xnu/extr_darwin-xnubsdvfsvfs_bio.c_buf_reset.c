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
struct TYPE_3__ {scalar_t__ b_error; int /*<<< orphan*/  b_flags; } ;

/* Variables and functions */
 int B_ASYNC ; 
 int B_DONE ; 
 int B_ERROR ; 
 int B_FUA ; 
 int B_INVAL ; 
 int B_NOCACHE ; 
 int B_READ ; 
 int B_WRITE ; 
 int /*<<< orphan*/  CLR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int) ; 

void
buf_reset(buf_t bp, int32_t io_flags) {
        
        CLR(bp->b_flags, (B_READ | B_WRITE | B_ERROR | B_DONE | B_INVAL | B_ASYNC | B_NOCACHE | B_FUA));
	SET(bp->b_flags, (io_flags & (B_ASYNC | B_READ | B_WRITE | B_NOCACHE)));

	bp->b_error = 0;
}