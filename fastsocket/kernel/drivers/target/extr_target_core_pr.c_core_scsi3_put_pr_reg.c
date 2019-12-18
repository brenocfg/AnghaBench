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
struct t10_pr_registration {int /*<<< orphan*/  pr_res_holders; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic_dec () ; 

__attribute__((used)) static void core_scsi3_put_pr_reg(struct t10_pr_registration *pr_reg)
{
	atomic_dec(&pr_reg->pr_res_holders);
	smp_mb__after_atomic_dec();
}