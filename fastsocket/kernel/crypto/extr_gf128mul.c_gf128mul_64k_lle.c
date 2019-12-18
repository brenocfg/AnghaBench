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
typedef  size_t u8 ;
struct gf128mul_64k {TYPE_1__** t; } ;
typedef  int /*<<< orphan*/  be128 ;
struct TYPE_2__ {int /*<<< orphan*/ * t; } ;

/* Variables and functions */
 int /*<<< orphan*/  be128_xor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void gf128mul_64k_lle(be128 *a, struct gf128mul_64k *t)
{
	u8 *ap = (u8 *)a;
	be128 r[1];
	int i;

	*r = t->t[0]->t[ap[0]];
	for (i = 1; i < 16; ++i)
		be128_xor(r, r, &t->t[i]->t[ap[i]]);
	*a = *r;
}