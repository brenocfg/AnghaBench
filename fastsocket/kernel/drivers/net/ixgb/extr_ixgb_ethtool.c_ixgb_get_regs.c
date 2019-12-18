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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ixgb_hw {int revision_id; int device_id; } ;
struct ixgb_adapter {struct ixgb_hw hw; } ;
struct ethtool_regs {int version; int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIS ; 
 int /*<<< orphan*/  APAE ; 
 int /*<<< orphan*/  ARD ; 
 int /*<<< orphan*/  CTRL0 ; 
 int /*<<< orphan*/  CTRL1 ; 
 int /*<<< orphan*/  EECD ; 
 int /*<<< orphan*/  FCRTH ; 
 int /*<<< orphan*/  FCRTL ; 
 int /*<<< orphan*/  ICR ; 
 int /*<<< orphan*/  ICS ; 
 int /*<<< orphan*/  IMC ; 
 int /*<<< orphan*/  IMS ; 
 int IXGB_ALL_RAR_ENTRIES ; 
 void* IXGB_GET_STAT (struct ixgb_adapter*,int /*<<< orphan*/ ) ; 
 void* IXGB_READ_REG (struct ixgb_hw*,int /*<<< orphan*/ ) ; 
 void* IXGB_READ_REG_ARRAY (struct ixgb_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MACA ; 
 int /*<<< orphan*/  MFS ; 
 int /*<<< orphan*/  MSCA ; 
 int /*<<< orphan*/  MSRWD ; 
 int /*<<< orphan*/  PAP ; 
 int /*<<< orphan*/  PCSC1 ; 
 int /*<<< orphan*/  PCSC2 ; 
 int /*<<< orphan*/  PCSS1 ; 
 int /*<<< orphan*/  PCSS2 ; 
 int /*<<< orphan*/  RAH ; 
 int /*<<< orphan*/  RAIDC ; 
 int /*<<< orphan*/  RAL ; 
 int /*<<< orphan*/  RCTL ; 
 int /*<<< orphan*/  RDBAH ; 
 int /*<<< orphan*/  RDBAL ; 
 int /*<<< orphan*/  RDH ; 
 int /*<<< orphan*/  RDLEN ; 
 int /*<<< orphan*/  RDT ; 
 int /*<<< orphan*/  RDTR ; 
 int /*<<< orphan*/  RXCSUM ; 
 int /*<<< orphan*/  RXDCTL ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  TCTL ; 
 int /*<<< orphan*/  TDBAH ; 
 int /*<<< orphan*/  TDBAL ; 
 int /*<<< orphan*/  TDH ; 
 int /*<<< orphan*/  TDLEN ; 
 int /*<<< orphan*/  TDT ; 
 int /*<<< orphan*/  TIDV ; 
 int /*<<< orphan*/  TSPMT ; 
 int /*<<< orphan*/  TXDCTL ; 
 int /*<<< orphan*/  UCCR ; 
 int /*<<< orphan*/  XPCSS ; 
 int /*<<< orphan*/  XPCSTC ; 
 int /*<<< orphan*/  bprch ; 
 int /*<<< orphan*/  bprcl ; 
 int /*<<< orphan*/  bptch ; 
 int /*<<< orphan*/  bptcl ; 
 int /*<<< orphan*/  crcerrs ; 
 int /*<<< orphan*/  dc ; 
 int /*<<< orphan*/  ecbc ; 
 int /*<<< orphan*/  gorch ; 
 int /*<<< orphan*/  gorcl ; 
 int /*<<< orphan*/  gotch ; 
 int /*<<< orphan*/  gotcl ; 
 int /*<<< orphan*/  gprch ; 
 int /*<<< orphan*/  gprcl ; 
 int /*<<< orphan*/  gptch ; 
 int /*<<< orphan*/  gptcl ; 
 int /*<<< orphan*/  ibic ; 
 int /*<<< orphan*/  icbc ; 
 int /*<<< orphan*/  jprch ; 
 int /*<<< orphan*/  jprcl ; 
 int /*<<< orphan*/  jptch ; 
 int /*<<< orphan*/  jptcl ; 
 int /*<<< orphan*/  lfc ; 
 int /*<<< orphan*/  mcfrc ; 
 int /*<<< orphan*/  mcftc ; 
 int /*<<< orphan*/  mpc ; 
 int /*<<< orphan*/  mprch ; 
 int /*<<< orphan*/  mprcl ; 
 int /*<<< orphan*/  mptch ; 
 int /*<<< orphan*/  mptcl ; 
 struct ixgb_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pfrc ; 
 int /*<<< orphan*/  pftc ; 
 int /*<<< orphan*/  plt64c ; 
 int /*<<< orphan*/  rfc ; 
 int /*<<< orphan*/  rjc ; 
 int /*<<< orphan*/  rlec ; 
 int /*<<< orphan*/  rnbc ; 
 int /*<<< orphan*/  roc ; 
 int /*<<< orphan*/  ruc ; 
 int /*<<< orphan*/  torh ; 
 int /*<<< orphan*/  torl ; 
 int /*<<< orphan*/  toth ; 
 int /*<<< orphan*/  totl ; 
 int /*<<< orphan*/  tprh ; 
 int /*<<< orphan*/  tprl ; 
 int /*<<< orphan*/  tpth ; 
 int /*<<< orphan*/  tptl ; 
 int /*<<< orphan*/  tsctc ; 
 int /*<<< orphan*/  tsctfc ; 
 int /*<<< orphan*/  uprch ; 
 int /*<<< orphan*/  uprcl ; 
 int /*<<< orphan*/  uptch ; 
 int /*<<< orphan*/  uptcl ; 
 int /*<<< orphan*/  vprch ; 
 int /*<<< orphan*/  vprcl ; 
 int /*<<< orphan*/  vptch ; 
 int /*<<< orphan*/  vptcl ; 
 int /*<<< orphan*/  xoffrxc ; 
 int /*<<< orphan*/  xofftxc ; 
 int /*<<< orphan*/  xonrxc ; 
 int /*<<< orphan*/  xontxc ; 

__attribute__((used)) static void
ixgb_get_regs(struct net_device *netdev,
		   struct ethtool_regs *regs, void *p)
{
	struct ixgb_adapter *adapter = netdev_priv(netdev);
	struct ixgb_hw *hw = &adapter->hw;
	u32 *reg = p;
	u32 *reg_start = reg;
	u8 i;

	/* the 1 (one) below indicates an attempt at versioning, if the
	 * interface in ethtool or the driver changes, this 1 should be
	 * incremented */
	regs->version = (1<<24) | hw->revision_id << 16 | hw->device_id;

	/* General Registers */
	*reg++ = IXGB_READ_REG(hw, CTRL0);	/*   0 */
	*reg++ = IXGB_READ_REG(hw, CTRL1);	/*   1 */
	*reg++ = IXGB_READ_REG(hw, STATUS);	/*   2 */
	*reg++ = IXGB_READ_REG(hw, EECD);	/*   3 */
	*reg++ = IXGB_READ_REG(hw, MFS);	/*   4 */

	/* Interrupt */
	*reg++ = IXGB_READ_REG(hw, ICR);	/*   5 */
	*reg++ = IXGB_READ_REG(hw, ICS);	/*   6 */
	*reg++ = IXGB_READ_REG(hw, IMS);	/*   7 */
	*reg++ = IXGB_READ_REG(hw, IMC);	/*   8 */

	/* Receive */
	*reg++ = IXGB_READ_REG(hw, RCTL);	/*   9 */
	*reg++ = IXGB_READ_REG(hw, FCRTL);	/*  10 */
	*reg++ = IXGB_READ_REG(hw, FCRTH);	/*  11 */
	*reg++ = IXGB_READ_REG(hw, RDBAL);	/*  12 */
	*reg++ = IXGB_READ_REG(hw, RDBAH);	/*  13 */
	*reg++ = IXGB_READ_REG(hw, RDLEN);	/*  14 */
	*reg++ = IXGB_READ_REG(hw, RDH);	/*  15 */
	*reg++ = IXGB_READ_REG(hw, RDT);	/*  16 */
	*reg++ = IXGB_READ_REG(hw, RDTR);	/*  17 */
	*reg++ = IXGB_READ_REG(hw, RXDCTL);	/*  18 */
	*reg++ = IXGB_READ_REG(hw, RAIDC);	/*  19 */
	*reg++ = IXGB_READ_REG(hw, RXCSUM);	/*  20 */

	/* there are 16 RAR entries in hardware, we only use 3 */
	for (i = 0; i < IXGB_ALL_RAR_ENTRIES; i++) {
		*reg++ = IXGB_READ_REG_ARRAY(hw, RAL, (i << 1)); /*21,...,51 */
		*reg++ = IXGB_READ_REG_ARRAY(hw, RAH, (i << 1)); /*22,...,52 */
	}

	/* Transmit */
	*reg++ = IXGB_READ_REG(hw, TCTL);	/*  53 */
	*reg++ = IXGB_READ_REG(hw, TDBAL);	/*  54 */
	*reg++ = IXGB_READ_REG(hw, TDBAH);	/*  55 */
	*reg++ = IXGB_READ_REG(hw, TDLEN);	/*  56 */
	*reg++ = IXGB_READ_REG(hw, TDH);	/*  57 */
	*reg++ = IXGB_READ_REG(hw, TDT);	/*  58 */
	*reg++ = IXGB_READ_REG(hw, TIDV);	/*  59 */
	*reg++ = IXGB_READ_REG(hw, TXDCTL);	/*  60 */
	*reg++ = IXGB_READ_REG(hw, TSPMT);	/*  61 */
	*reg++ = IXGB_READ_REG(hw, PAP);	/*  62 */

	/* Physical */
	*reg++ = IXGB_READ_REG(hw, PCSC1);	/*  63 */
	*reg++ = IXGB_READ_REG(hw, PCSC2);	/*  64 */
	*reg++ = IXGB_READ_REG(hw, PCSS1);	/*  65 */
	*reg++ = IXGB_READ_REG(hw, PCSS2);	/*  66 */
	*reg++ = IXGB_READ_REG(hw, XPCSS);	/*  67 */
	*reg++ = IXGB_READ_REG(hw, UCCR);	/*  68 */
	*reg++ = IXGB_READ_REG(hw, XPCSTC);	/*  69 */
	*reg++ = IXGB_READ_REG(hw, MACA);	/*  70 */
	*reg++ = IXGB_READ_REG(hw, APAE);	/*  71 */
	*reg++ = IXGB_READ_REG(hw, ARD);	/*  72 */
	*reg++ = IXGB_READ_REG(hw, AIS);	/*  73 */
	*reg++ = IXGB_READ_REG(hw, MSCA);	/*  74 */
	*reg++ = IXGB_READ_REG(hw, MSRWD);	/*  75 */

	/* Statistics */
	*reg++ = IXGB_GET_STAT(adapter, tprl);	/*  76 */
	*reg++ = IXGB_GET_STAT(adapter, tprh);	/*  77 */
	*reg++ = IXGB_GET_STAT(adapter, gprcl);	/*  78 */
	*reg++ = IXGB_GET_STAT(adapter, gprch);	/*  79 */
	*reg++ = IXGB_GET_STAT(adapter, bprcl);	/*  80 */
	*reg++ = IXGB_GET_STAT(adapter, bprch);	/*  81 */
	*reg++ = IXGB_GET_STAT(adapter, mprcl);	/*  82 */
	*reg++ = IXGB_GET_STAT(adapter, mprch);	/*  83 */
	*reg++ = IXGB_GET_STAT(adapter, uprcl);	/*  84 */
	*reg++ = IXGB_GET_STAT(adapter, uprch);	/*  85 */
	*reg++ = IXGB_GET_STAT(adapter, vprcl);	/*  86 */
	*reg++ = IXGB_GET_STAT(adapter, vprch);	/*  87 */
	*reg++ = IXGB_GET_STAT(adapter, jprcl);	/*  88 */
	*reg++ = IXGB_GET_STAT(adapter, jprch);	/*  89 */
	*reg++ = IXGB_GET_STAT(adapter, gorcl);	/*  90 */
	*reg++ = IXGB_GET_STAT(adapter, gorch);	/*  91 */
	*reg++ = IXGB_GET_STAT(adapter, torl);	/*  92 */
	*reg++ = IXGB_GET_STAT(adapter, torh);	/*  93 */
	*reg++ = IXGB_GET_STAT(adapter, rnbc);	/*  94 */
	*reg++ = IXGB_GET_STAT(adapter, ruc);	/*  95 */
	*reg++ = IXGB_GET_STAT(adapter, roc);	/*  96 */
	*reg++ = IXGB_GET_STAT(adapter, rlec);	/*  97 */
	*reg++ = IXGB_GET_STAT(adapter, crcerrs);	/*  98 */
	*reg++ = IXGB_GET_STAT(adapter, icbc);	/*  99 */
	*reg++ = IXGB_GET_STAT(adapter, ecbc);	/* 100 */
	*reg++ = IXGB_GET_STAT(adapter, mpc);	/* 101 */
	*reg++ = IXGB_GET_STAT(adapter, tptl);	/* 102 */
	*reg++ = IXGB_GET_STAT(adapter, tpth);	/* 103 */
	*reg++ = IXGB_GET_STAT(adapter, gptcl);	/* 104 */
	*reg++ = IXGB_GET_STAT(adapter, gptch);	/* 105 */
	*reg++ = IXGB_GET_STAT(adapter, bptcl);	/* 106 */
	*reg++ = IXGB_GET_STAT(adapter, bptch);	/* 107 */
	*reg++ = IXGB_GET_STAT(adapter, mptcl);	/* 108 */
	*reg++ = IXGB_GET_STAT(adapter, mptch);	/* 109 */
	*reg++ = IXGB_GET_STAT(adapter, uptcl);	/* 110 */
	*reg++ = IXGB_GET_STAT(adapter, uptch);	/* 111 */
	*reg++ = IXGB_GET_STAT(adapter, vptcl);	/* 112 */
	*reg++ = IXGB_GET_STAT(adapter, vptch);	/* 113 */
	*reg++ = IXGB_GET_STAT(adapter, jptcl);	/* 114 */
	*reg++ = IXGB_GET_STAT(adapter, jptch);	/* 115 */
	*reg++ = IXGB_GET_STAT(adapter, gotcl);	/* 116 */
	*reg++ = IXGB_GET_STAT(adapter, gotch);	/* 117 */
	*reg++ = IXGB_GET_STAT(adapter, totl);	/* 118 */
	*reg++ = IXGB_GET_STAT(adapter, toth);	/* 119 */
	*reg++ = IXGB_GET_STAT(adapter, dc);	/* 120 */
	*reg++ = IXGB_GET_STAT(adapter, plt64c);	/* 121 */
	*reg++ = IXGB_GET_STAT(adapter, tsctc);	/* 122 */
	*reg++ = IXGB_GET_STAT(adapter, tsctfc);	/* 123 */
	*reg++ = IXGB_GET_STAT(adapter, ibic);	/* 124 */
	*reg++ = IXGB_GET_STAT(adapter, rfc);	/* 125 */
	*reg++ = IXGB_GET_STAT(adapter, lfc);	/* 126 */
	*reg++ = IXGB_GET_STAT(adapter, pfrc);	/* 127 */
	*reg++ = IXGB_GET_STAT(adapter, pftc);	/* 128 */
	*reg++ = IXGB_GET_STAT(adapter, mcfrc);	/* 129 */
	*reg++ = IXGB_GET_STAT(adapter, mcftc);	/* 130 */
	*reg++ = IXGB_GET_STAT(adapter, xonrxc);	/* 131 */
	*reg++ = IXGB_GET_STAT(adapter, xontxc);	/* 132 */
	*reg++ = IXGB_GET_STAT(adapter, xoffrxc);	/* 133 */
	*reg++ = IXGB_GET_STAT(adapter, xofftxc);	/* 134 */
	*reg++ = IXGB_GET_STAT(adapter, rjc);	/* 135 */

	regs->len = (reg - reg_start) * sizeof(u32);
}