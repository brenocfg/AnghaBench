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
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int /*<<< orphan*/  if_fake_ref ;

/* Variables and functions */
 scalar_t__ ifnet_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static if_fake_ref
ifnet_get_if_fake(ifnet_t ifp)
{
	return ((if_fake_ref)ifnet_softc(ifp));
}