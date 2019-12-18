#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gf128mul_4k {int /*<<< orphan*/ * t; } ;
typedef  int /*<<< orphan*/  be128 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  be128_xor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gf128mul_x_bbe (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct gf128mul_4k* kzalloc (int,int /*<<< orphan*/ ) ; 

struct gf128mul_4k *gf128mul_init_4k_bbe(const be128 *g)
{
	struct gf128mul_4k *t;
	int j, k;

	t = kzalloc(sizeof(*t), GFP_KERNEL);
	if (!t)
		goto out;

	t->t[1] = *g;
	for (j = 1; j <= 64; j <<= 1)
		gf128mul_x_bbe(&t->t[j + j], &t->t[j]);

	for (j = 2; j < 256; j += j)
		for (k = 1; k < j; ++k)
			be128_xor(&t->t[j + k], &t->t[j], &t->t[k]);

out:
	return t;
}