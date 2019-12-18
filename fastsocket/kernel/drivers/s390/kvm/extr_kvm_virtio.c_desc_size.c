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
struct kvm_vqconfig {int dummy; } ;
struct kvm_device_desc {int num_vq; int feature_len; int config_len; } ;

/* Variables and functions */

__attribute__((used)) static unsigned desc_size(const struct kvm_device_desc *desc)
{
	return sizeof(*desc)
		+ desc->num_vq * sizeof(struct kvm_vqconfig)
		+ desc->feature_len * 2
		+ desc->config_len;
}