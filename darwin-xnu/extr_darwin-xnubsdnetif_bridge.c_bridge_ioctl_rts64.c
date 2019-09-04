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
struct ifbareq64 {int dummy; } ;
struct ifbaconf64 {int dummy; } ;
struct bridge_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_IOCTL_RTS ; 

__attribute__((used)) static int
bridge_ioctl_rts64(struct bridge_softc *sc, void *arg)
{
	struct ifbaconf64 *bac = arg;
	struct ifbareq64 bareq;
	int error = 0;

	BRIDGE_IOCTL_RTS;
	return (error);
}