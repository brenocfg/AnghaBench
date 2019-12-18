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
struct vio_driver_state {TYPE_1__* ver_table; int /*<<< orphan*/  hs_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;

/* Variables and functions */
 int /*<<< orphan*/  HS ; 
 int /*<<< orphan*/  VIO_HS_INVALID ; 
 int send_version (struct vio_driver_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viodbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int start_handshake(struct vio_driver_state *vio)
{
	int err;

	viodbg(HS, "START HANDSHAKE\n");

	vio->hs_state = VIO_HS_INVALID;

	err = send_version(vio,
			   vio->ver_table[0].major,
			   vio->ver_table[0].minor);
	if (err < 0)
		return err;

	return 0;
}