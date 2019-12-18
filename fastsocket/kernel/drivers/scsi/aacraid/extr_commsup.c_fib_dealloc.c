#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ XferState; } ;
struct hw_fib {TYPE_1__ header; } ;
struct fib {struct hw_fib* hw_fib_va; } ;

/* Variables and functions */

__attribute__((used)) static void fib_dealloc(struct fib * fibptr)
{
	struct hw_fib *hw_fib = fibptr->hw_fib_va;
	hw_fib->header.XferState = 0;
}