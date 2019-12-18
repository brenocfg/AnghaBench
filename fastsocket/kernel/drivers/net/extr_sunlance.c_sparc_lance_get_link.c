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
typedef  int u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static u32 sparc_lance_get_link(struct net_device *dev)
{
	/* We really do not keep track of this, but this
	 * is better than not reporting anything at all.
	 */
	return 1;
}