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
struct spu_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spu_free_lscsa (struct spu_state*) ; 

void spu_fini_csa(struct spu_state *csa)
{
	spu_free_lscsa(csa);
}