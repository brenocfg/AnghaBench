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
struct electra_cf_socket {int gpio_detect; scalar_t__ gpio_base; } ;

/* Variables and functions */
 unsigned int in_le32 (scalar_t__) ; 

__attribute__((used)) static int electra_cf_present(struct electra_cf_socket *cf)
{
	unsigned int gpio;

	gpio = in_le32(cf->gpio_base+0x40);
	return !(gpio & (1 << cf->gpio_detect));
}