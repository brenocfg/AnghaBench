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
struct TYPE_2__ {int /*<<< orphan*/ * r_8; } ;
typedef  int /*<<< orphan*/  M68K_READ ;

/* Variables and functions */
 TYPE_1__ rw_funcs ; 

__attribute__((used)) static void M68KMusashiSetReadB(M68K_READ *Func) {
   rw_funcs.r_8 = Func;
}