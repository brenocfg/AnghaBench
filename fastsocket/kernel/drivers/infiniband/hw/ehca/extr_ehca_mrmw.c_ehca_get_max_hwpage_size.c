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
typedef  int /*<<< orphan*/  u64 ;
struct ehca_shca {int /*<<< orphan*/  hca_cap_mr_pgsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  rounddown_pow_of_two (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 ehca_get_max_hwpage_size(struct ehca_shca *shca)
{
	return rounddown_pow_of_two(shca->hca_cap_mr_pgsize);
}