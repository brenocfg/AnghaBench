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
struct vio_port {int dummy; } ;
struct srp_target {scalar_t__ ldata; } ;

/* Variables and functions */

__attribute__((used)) static struct vio_port *target_to_port(struct srp_target *target)
{
	return (struct vio_port *) target->ldata;
}