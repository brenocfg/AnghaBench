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
typedef  int /*<<< orphan*/  u8 ;
struct kvm_device_desc {int feature_len; } ;

/* Variables and functions */
 int /*<<< orphan*/ * kvm_vq_features (struct kvm_device_desc const*) ; 

__attribute__((used)) static u8 *kvm_vq_configspace(const struct kvm_device_desc *desc)
{
	return kvm_vq_features(desc) + desc->feature_len * 2;
}