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
struct ia64_pal_retval {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_PAL_STATUS_SUCCESS (struct ia64_pal_retval) ; 

__attribute__((used)) static struct ia64_pal_retval pal_platform_addr(struct kvm_vcpu *vcpu)
{

	struct ia64_pal_retval result;

	INIT_PAL_STATUS_SUCCESS(result);
	return result;
}