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
struct kprobe {int dummy; } ;
typedef  struct kprobe* __get_cpu_var ;

/* Variables and functions */

__attribute__((used)) static inline void set_kprobe_instance(struct kprobe *kp)
{
	__get_cpu_var(kprobe_instance) = kp;
}