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
 int /*<<< orphan*/  PAL_CACHE_SUMMARY ; 
 int /*<<< orphan*/  PAL_CALL (struct ia64_pal_retval,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct ia64_pal_retval pal_cache_summary(struct kvm_vcpu *vcpu)
{

	struct ia64_pal_retval result;

	PAL_CALL(result, PAL_CACHE_SUMMARY, 0, 0, 0);
	return result;
}