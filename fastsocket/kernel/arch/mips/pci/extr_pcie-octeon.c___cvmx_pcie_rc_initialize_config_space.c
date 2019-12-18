#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int cere; int nfere; int fere; } ;
union cvmx_pciercx_cfg075 {void* u32; TYPE_12__ s; } ;
struct TYPE_20__ {int ge; int ce; } ;
union cvmx_pciercx_cfg070 {void* u32; TYPE_3__ s; } ;
struct TYPE_15__ {int secee; int sefee; int senfee; int pmeie; } ;
union cvmx_pciercx_cfg035 {void* u32; TYPE_11__ s; } ;
struct TYPE_17__ {int hpint_en; int dlls_en; int ccint_en; } ;
union cvmx_pciercx_cfg034 {void* u32; TYPE_13__ s; } ;
struct TYPE_22__ {scalar_t__ aslpc; } ;
union cvmx_pciercx_cfg032 {void* u32; TYPE_5__ s; } ;
struct TYPE_18__ {int ro_en; int ns_en; int ce_en; int nfe_en; int fe_en; int ur_en; scalar_t__ mrrs; scalar_t__ mps; } ;
union cvmx_pciercx_cfg030 {void* u32; TYPE_1__ s; } ;
struct TYPE_14__ {scalar_t__ umem_limit; } ;
union cvmx_pciercx_cfg011 {void* u32; TYPE_10__ s; } ;
struct TYPE_26__ {int umem_base; } ;
union cvmx_pciercx_cfg010 {void* u32; TYPE_9__ s; } ;
struct TYPE_25__ {int lmem_base; scalar_t__ lmem_limit; } ;
union cvmx_pciercx_cfg009 {void* u32; TYPE_8__ s; } ;
struct TYPE_24__ {int mb_addr; scalar_t__ ml_addr; } ;
union cvmx_pciercx_cfg008 {void* u32; TYPE_7__ s; } ;
struct TYPE_23__ {int pbnum; int sbnum; int subbnum; } ;
union cvmx_pciercx_cfg006 {void* u32; TYPE_6__ s; } ;
struct TYPE_21__ {int msae; int me; int i_dis; int see; } ;
union cvmx_pciercx_cfg001 {void* u32; TYPE_4__ s; } ;
struct TYPE_19__ {scalar_t__ mrrs; scalar_t__ mps; } ;
union cvmx_npei_ctl_status2 {int /*<<< orphan*/  u64; TYPE_2__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_PCIERCX_CFG001 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG006 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG008 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG009 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG010 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG011 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG030 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG032 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG034 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG035 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG066 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG069 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG070 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG075 (int) ; 
 int /*<<< orphan*/  CVMX_PEXP_NPEI_CTL_STATUS2 ; 
 void* cvmx_pcie_cfgx_read (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_pcie_cfgx_write (int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __cvmx_pcie_rc_initialize_config_space(int pcie_port)
{
	union cvmx_pciercx_cfg030 pciercx_cfg030;
	union cvmx_npei_ctl_status2 npei_ctl_status2;
	union cvmx_pciercx_cfg070 pciercx_cfg070;
	union cvmx_pciercx_cfg001 pciercx_cfg001;
	union cvmx_pciercx_cfg032 pciercx_cfg032;
	union cvmx_pciercx_cfg006 pciercx_cfg006;
	union cvmx_pciercx_cfg008 pciercx_cfg008;
	union cvmx_pciercx_cfg009 pciercx_cfg009;
	union cvmx_pciercx_cfg010 pciercx_cfg010;
	union cvmx_pciercx_cfg011 pciercx_cfg011;
	union cvmx_pciercx_cfg035 pciercx_cfg035;
	union cvmx_pciercx_cfg075 pciercx_cfg075;
	union cvmx_pciercx_cfg034 pciercx_cfg034;

	/* Max Payload Size (PCIE*_CFG030[MPS]) */
	/* Max Read Request Size (PCIE*_CFG030[MRRS]) */
	/* Relaxed-order, no-snoop enables (PCIE*_CFG030[RO_EN,NS_EN] */
	/* Error Message Enables (PCIE*_CFG030[CE_EN,NFE_EN,FE_EN,UR_EN]) */
	pciercx_cfg030.u32 =
		cvmx_pcie_cfgx_read(pcie_port, CVMX_PCIERCX_CFG030(pcie_port));
	/*
	 * Max payload size = 128 bytes for best Octeon DMA
	 * performance.
	 */
	pciercx_cfg030.s.mps = 0;
	/*
	 * Max read request size = 128 bytes for best Octeon DMA
	 * performance.
	 */
	pciercx_cfg030.s.mrrs = 0;
	/* Enable relaxed ordering. */
	pciercx_cfg030.s.ro_en = 1;
	/* Enable no snoop. */
	pciercx_cfg030.s.ns_en = 1;
	/* Correctable error reporting enable. */
	pciercx_cfg030.s.ce_en = 1;
	/* Non-fatal error reporting enable. */
	pciercx_cfg030.s.nfe_en = 1;
	/* Fatal error reporting enable. */
	pciercx_cfg030.s.fe_en = 1;
	/* Unsupported request reporting enable. */
	pciercx_cfg030.s.ur_en = 1;
	cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG030(pcie_port),
			     pciercx_cfg030.u32);

	/*
	 * Max Payload Size (NPEI_CTL_STATUS2[MPS]) must match
	 * PCIE*_CFG030[MPS]
	 *
	 * Max Read Request Size (NPEI_CTL_STATUS2[MRRS]) must not
	 * exceed PCIE*_CFG030[MRRS].
	 */
	npei_ctl_status2.u64 = cvmx_read_csr(CVMX_PEXP_NPEI_CTL_STATUS2);
	/* Max payload size = 128 bytes for best Octeon DMA performance */
	npei_ctl_status2.s.mps = 0;
	/* Max read request size = 128 bytes for best Octeon DMA performance */
	npei_ctl_status2.s.mrrs = 0;
	cvmx_write_csr(CVMX_PEXP_NPEI_CTL_STATUS2, npei_ctl_status2.u64);

	/* ECRC Generation (PCIE*_CFG070[GE,CE]) */
	pciercx_cfg070.u32 =
		cvmx_pcie_cfgx_read(pcie_port, CVMX_PCIERCX_CFG070(pcie_port));
	pciercx_cfg070.s.ge = 1;	/* ECRC generation enable. */
	pciercx_cfg070.s.ce = 1;	/* ECRC check enable. */
	cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG070(pcie_port),
			     pciercx_cfg070.u32);

	/*
	 * Access Enables (PCIE*_CFG001[MSAE,ME]) ME and MSAE should
	 * always be set.
	 *
	 * Interrupt Disable (PCIE*_CFG001[I_DIS]) System Error
	 * Message Enable (PCIE*_CFG001[SEE])
	 */
	pciercx_cfg001.u32 =
		cvmx_pcie_cfgx_read(pcie_port, CVMX_PCIERCX_CFG001(pcie_port));
	pciercx_cfg001.s.msae = 1;	/* Memory space enable. */
	pciercx_cfg001.s.me = 1;	/* Bus master enable. */
	pciercx_cfg001.s.i_dis = 1;	/* INTx assertion disable. */
	pciercx_cfg001.s.see = 1;	/* SERR# enable */
	cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG001(pcie_port),
			pciercx_cfg001.u32);

	/* Advanced Error Recovery Message Enables */
	/* (PCIE*_CFG066,PCIE*_CFG067,PCIE*_CFG069) */
	cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG066(pcie_port), 0);
	/* Use CVMX_PCIERCX_CFG067 hardware default */
	cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG069(pcie_port), 0);

	/* Active State Power Management (PCIE*_CFG032[ASLPC]) */
	pciercx_cfg032.u32 =
		cvmx_pcie_cfgx_read(pcie_port, CVMX_PCIERCX_CFG032(pcie_port));
	pciercx_cfg032.s.aslpc = 0;	/* Active state Link PM control. */
	cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG032(pcie_port),
			     pciercx_cfg032.u32);

	/* Entrance Latencies (PCIE*_CFG451[L0EL,L1EL]) */

	/*
	 * Link Width Mode (PCIERCn_CFG452[LME]) - Set during
	 * cvmx_pcie_rc_initialize_link()
	 *
	 * Primary Bus Number (PCIERCn_CFG006[PBNUM])
	 *
	 * We set the primary bus number to 1 so IDT bridges are
	 * happy. They don't like zero.
	 */
	pciercx_cfg006.u32 = 0;
	pciercx_cfg006.s.pbnum = 1;
	pciercx_cfg006.s.sbnum = 1;
	pciercx_cfg006.s.subbnum = 1;
	cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG006(pcie_port),
			     pciercx_cfg006.u32);

	/*
	 * Memory-mapped I/O BAR (PCIERCn_CFG008)
	 * Most applications should disable the memory-mapped I/O BAR by
	 * setting PCIERCn_CFG008[ML_ADDR] < PCIERCn_CFG008[MB_ADDR]
	 */
	pciercx_cfg008.u32 = 0;
	pciercx_cfg008.s.mb_addr = 0x100;
	pciercx_cfg008.s.ml_addr = 0;
	cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG008(pcie_port),
			     pciercx_cfg008.u32);

	/*
	 * Prefetchable BAR (PCIERCn_CFG009,PCIERCn_CFG010,PCIERCn_CFG011)
	 * Most applications should disable the prefetchable BAR by setting
	 * PCIERCn_CFG011[UMEM_LIMIT],PCIERCn_CFG009[LMEM_LIMIT] <
	 * PCIERCn_CFG010[UMEM_BASE],PCIERCn_CFG009[LMEM_BASE]
	 */
	pciercx_cfg009.u32 =
		cvmx_pcie_cfgx_read(pcie_port, CVMX_PCIERCX_CFG009(pcie_port));
	pciercx_cfg010.u32 =
		cvmx_pcie_cfgx_read(pcie_port, CVMX_PCIERCX_CFG010(pcie_port));
	pciercx_cfg011.u32 =
		cvmx_pcie_cfgx_read(pcie_port, CVMX_PCIERCX_CFG011(pcie_port));
	pciercx_cfg009.s.lmem_base = 0x100;
	pciercx_cfg009.s.lmem_limit = 0;
	pciercx_cfg010.s.umem_base = 0x100;
	pciercx_cfg011.s.umem_limit = 0;
	cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG009(pcie_port),
			     pciercx_cfg009.u32);
	cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG010(pcie_port),
			     pciercx_cfg010.u32);
	cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG011(pcie_port),
			     pciercx_cfg011.u32);

	/*
	 * System Error Interrupt Enables (PCIERCn_CFG035[SECEE,SEFEE,SENFEE])
	 * PME Interrupt Enables (PCIERCn_CFG035[PMEIE])
	 */
	pciercx_cfg035.u32 =
		cvmx_pcie_cfgx_read(pcie_port, CVMX_PCIERCX_CFG035(pcie_port));
	/* System error on correctable error enable. */
	pciercx_cfg035.s.secee = 1;
	/* System error on fatal error enable. */
	pciercx_cfg035.s.sefee = 1;
	/* System error on non-fatal error enable. */
	pciercx_cfg035.s.senfee = 1;
	/* PME interrupt enable. */
	pciercx_cfg035.s.pmeie = 1;
	cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG035(pcie_port),
			     pciercx_cfg035.u32);

	/*
	 * Advanced Error Recovery Interrupt Enables
	 * (PCIERCn_CFG075[CERE,NFERE,FERE])
	 */
	pciercx_cfg075.u32 =
		cvmx_pcie_cfgx_read(pcie_port, CVMX_PCIERCX_CFG075(pcie_port));
	/* Correctable error reporting enable. */
	pciercx_cfg075.s.cere = 1;
	/* Non-fatal error reporting enable. */
	pciercx_cfg075.s.nfere = 1;
	/* Fatal error reporting enable. */
	pciercx_cfg075.s.fere = 1;
	cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG075(pcie_port),
			     pciercx_cfg075.u32);

	/* HP Interrupt Enables (PCIERCn_CFG034[HPINT_EN],
	 * PCIERCn_CFG034[DLLS_EN,CCINT_EN])
	 */
	pciercx_cfg034.u32 =
		cvmx_pcie_cfgx_read(pcie_port, CVMX_PCIERCX_CFG034(pcie_port));
	/* Hot-plug interrupt enable. */
	pciercx_cfg034.s.hpint_en = 1;
	/* Data Link Layer state changed enable */
	pciercx_cfg034.s.dlls_en = 1;
	/* Command completed interrupt enable. */
	pciercx_cfg034.s.ccint_en = 1;
	cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG034(pcie_port),
			     pciercx_cfg034.u32);
}