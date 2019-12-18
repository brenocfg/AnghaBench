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
union cvmx_pip_prt_tagx {int /*<<< orphan*/  u64; } ;
union cvmx_pip_prt_cfgx {int /*<<< orphan*/  u64; } ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_PIP_PRT_CFGX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_PIP_PRT_TAGX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cvmx_pip_config_port(uint64_t port_num,
					union cvmx_pip_prt_cfgx port_cfg,
					union cvmx_pip_prt_tagx port_tag_cfg)
{
	cvmx_write_csr(CVMX_PIP_PRT_CFGX(port_num), port_cfg.u64);
	cvmx_write_csr(CVMX_PIP_PRT_TAGX(port_num), port_tag_cfg.u64);
}