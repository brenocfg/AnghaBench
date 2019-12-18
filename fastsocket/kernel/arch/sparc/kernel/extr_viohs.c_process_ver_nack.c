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
struct vio_version {int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct vio_ver_info {scalar_t__ major; scalar_t__ minor; int /*<<< orphan*/  dev_class; } ;
struct vio_driver_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HS ; 
 struct vio_version* find_by_major (struct vio_driver_state*,scalar_t__) ; 
 int handshake_failure (struct vio_driver_state*) ; 
 scalar_t__ send_version (struct vio_driver_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viodbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_ver_nack(struct vio_driver_state *vio,
			    struct vio_ver_info *pkt)
{
	struct vio_version *nver;

	viodbg(HS, "GOT VERSION NACK maj[%u] min[%u] devclass[%u]\n",
	       pkt->major, pkt->minor, pkt->dev_class);

	if (pkt->major == 0 && pkt->minor == 0)
		return handshake_failure(vio);
	nver = find_by_major(vio, pkt->major);
	if (!nver)
		return handshake_failure(vio);

	if (send_version(vio, nver->major, nver->minor) < 0)
		return handshake_failure(vio);

	return 0;
}