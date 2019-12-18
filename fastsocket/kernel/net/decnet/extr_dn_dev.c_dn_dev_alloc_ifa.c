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
struct dn_ifaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct dn_ifaddr* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dn_ifaddr *dn_dev_alloc_ifa(void)
{
	struct dn_ifaddr *ifa;

	ifa = kzalloc(sizeof(*ifa), GFP_KERNEL);

	return ifa;
}