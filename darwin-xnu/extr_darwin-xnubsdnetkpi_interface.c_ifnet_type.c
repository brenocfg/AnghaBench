#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  TYPE_2__* ifnet_t ;
struct TYPE_4__ {int /*<<< orphan*/  ifi_type; } ;
struct TYPE_5__ {TYPE_1__ if_data; } ;

/* Variables and functions */

u_char
ifnet_type(ifnet_t interface)
{
	return ((interface == NULL) ? 0 : interface->if_data.ifi_type);
}