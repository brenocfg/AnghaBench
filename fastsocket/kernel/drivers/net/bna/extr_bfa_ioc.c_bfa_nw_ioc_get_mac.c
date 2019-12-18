#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bfa_ioc {TYPE_1__* attr; } ;
typedef  int /*<<< orphan*/  mac_t ;
struct TYPE_2__ {int /*<<< orphan*/  mac; } ;

/* Variables and functions */

mac_t
bfa_nw_ioc_get_mac(struct bfa_ioc *ioc)
{
	return ioc->attr->mac;
}