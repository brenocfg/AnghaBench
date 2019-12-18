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
struct net_device {int /*<<< orphan*/  type; scalar_t__ addr_len; } ;

/* Variables and functions */
 int NDISC_OPT_SPACE (scalar_t__) ; 
 scalar_t__ ndisc_addr_option_pad (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ndisc_opt_addr_space(struct net_device *dev)
{
	return NDISC_OPT_SPACE(dev->addr_len + ndisc_addr_option_pad(dev->type));
}