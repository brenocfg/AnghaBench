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
struct kvm_vcpu {int dummy; } ;
struct ia64_pal_retval {scalar_t__ v0; scalar_t__ v2; int /*<<< orphan*/  v1; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAL_CALL (struct ia64_pal_retval,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAL_FREQ_BASE ; 
 int /*<<< orphan*/  SAL_FREQ_BASE_PLATFORM ; 
 int /*<<< orphan*/  ia64_sal_freq_base (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ia64_pal_retval pal_freq_base(struct kvm_vcpu *vcpu)
{

	struct ia64_pal_retval result;

	PAL_CALL(result, PAL_FREQ_BASE, 0, 0, 0);

	/*
	 * PAL_FREQ_BASE may not be implemented in some platforms,
	 * call SAL instead.
	 */
	if (result.v0 == 0) {
		result.status = ia64_sal_freq_base(SAL_FREQ_BASE_PLATFORM,
							&result.v0,
							&result.v1);
		result.v2 = 0;
	}

	return result;
}