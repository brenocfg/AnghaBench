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
struct netvsc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netvsc_destroy_recv_buf (struct netvsc_device*) ; 

__attribute__((used)) static void netvsc_disconnect_vsp(struct netvsc_device *net_device)
{
	netvsc_destroy_recv_buf(net_device);
}