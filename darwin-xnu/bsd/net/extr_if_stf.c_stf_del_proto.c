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
struct stf_softc {scalar_t__ sc_protocol_family; } ;
typedef  scalar_t__ protocol_family_t ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 scalar_t__ ifnet_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static errno_t
stf_del_proto(
	ifnet_t				ifp,
	protocol_family_t	protocol_family)
{
	if (((struct stf_softc*)ifnet_softc(ifp))->sc_protocol_family == protocol_family)
		((struct stf_softc*)ifnet_softc(ifp))->sc_protocol_family = 0;
	
	return 0;
}