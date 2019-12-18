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
typedef  int /*<<< orphan*/  rcc_real_ty ;
struct TYPE_3__ {int /*<<< orphan*/  d; } ;
typedef  TYPE_1__ Value ;

/* Variables and functions */
 int /*<<< orphan*/  rcc_real (unsigned int,unsigned int) ; 
 size_t swap ; 

__attribute__((used)) static rcc_real_ty mk_real(int size, Value v) {
	unsigned *p = (unsigned *)&v.d;
	return rcc_real(p[swap], p[1-swap]);
}