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
struct TYPE_2__ {int /*<<< orphan*/  qos; } ;
union cvmx_pip_qos_vlanx {scalar_t__ u64; TYPE_1__ s; } ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_PIP_QOS_VLANX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void cvmx_pip_config_vlan_qos(uint64_t vlan_priority,
					    uint64_t qos)
{
	union cvmx_pip_qos_vlanx pip_qos_vlanx;
	pip_qos_vlanx.u64 = 0;
	pip_qos_vlanx.s.qos = qos;
	cvmx_write_csr(CVMX_PIP_QOS_VLANX(vlan_priority), pip_qos_vlanx.u64);
}