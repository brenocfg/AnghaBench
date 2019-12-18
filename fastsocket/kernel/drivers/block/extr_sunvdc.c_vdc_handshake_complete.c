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
struct vio_driver_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WAITING_FOR_LINK_UP ; 
 int /*<<< orphan*/  vdc_finish (struct vio_driver_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vdc_handshake_complete(struct vio_driver_state *vio)
{
	vdc_finish(vio, 0, WAITING_FOR_LINK_UP);
}