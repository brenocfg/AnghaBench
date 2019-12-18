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
typedef  void u8 ;
struct lguest_device_desc {scalar_t__ num_vq; } ;

/* Variables and functions */
 scalar_t__ lg_vq (struct lguest_device_desc const*) ; 

__attribute__((used)) static u8 *lg_features(const struct lguest_device_desc *desc)
{
	return (void *)(lg_vq(desc) + desc->num_vq);
}