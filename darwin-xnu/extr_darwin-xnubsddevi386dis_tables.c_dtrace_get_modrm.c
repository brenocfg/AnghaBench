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
typedef  int /*<<< orphan*/  uint_t ;
struct TYPE_4__ {int d86_got_modrm; int d86_rmindex; int d86_len; } ;
typedef  TYPE_1__ dis86_t ;

/* Variables and functions */
 int /*<<< orphan*/  dtrace_get_SIB (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dtrace_get_modrm(dis86_t *x, uint_t *mode, uint_t *reg, uint_t *r_m)
{
	if (x->d86_got_modrm == 0) {
		if (x->d86_rmindex == -1)
			x->d86_rmindex = x->d86_len;
		dtrace_get_SIB(x, mode, reg, r_m);
		x->d86_got_modrm = 1;
	}
}