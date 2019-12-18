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
typedef  int u32 ;
struct ixp2400_msf_parameters {int /*<<< orphan*/  tx_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXP2000_MSF_TX_CONTROL ; 
 int ixp2000_reg_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixp2000_reg_write (int /*<<< orphan*/ ,int) ; 
 int ixp2400_msf_valid_channels (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixp2400_msf_enable_tx(struct ixp2400_msf_parameters *mp)
{
	u32 value;

	value = ixp2000_reg_read(IXP2000_MSF_TX_CONTROL) & 0x0fffffff;
	value |= ixp2400_msf_valid_channels(mp->tx_mode) << 28;
	ixp2000_reg_write(IXP2000_MSF_TX_CONTROL, value);
}