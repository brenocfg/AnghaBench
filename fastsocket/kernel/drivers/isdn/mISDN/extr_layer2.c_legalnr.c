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
struct layer2 {unsigned int va; int vs; int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_MOD128 ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int
legalnr(struct layer2 *l2, unsigned int nr)
{
	if (test_bit(FLG_MOD128, &l2->flag))
		return ((nr - l2->va) % 128) <= ((l2->vs - l2->va) % 128);
	else
		return ((nr - l2->va) % 8) <= ((l2->vs - l2->va) % 8);
}