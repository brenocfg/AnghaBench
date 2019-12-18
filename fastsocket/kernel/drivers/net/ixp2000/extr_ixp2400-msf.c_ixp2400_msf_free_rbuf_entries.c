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
struct ixp2400_msf_parameters {int rx_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXP2000_MSF_RBUF_ELEMENT_DONE ; 
 int IXP2400_RX_MODE_RBUF_SIZE_128 ; 
 int IXP2400_RX_MODE_RBUF_SIZE_256 ; 
 int IXP2400_RX_MODE_RBUF_SIZE_64 ; 
 int IXP2400_RX_MODE_RBUF_SIZE_MASK ; 
 int /*<<< orphan*/  ixp2000_reg_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ixp2400_msf_free_rbuf_entries(struct ixp2400_msf_parameters *mp)
{
	int size_bits;
	int i;

	/*
	 * Work around IXP2400 erratum #69 (silent RBUF-to-DRAM transfer
	 * corruption) in the Intel-recommended way: do not add the RBUF
	 * elements susceptible to corruption to the freelist.
	 */
	size_bits = mp->rx_mode & IXP2400_RX_MODE_RBUF_SIZE_MASK;
	if (size_bits == IXP2400_RX_MODE_RBUF_SIZE_64) {
		for (i = 1; i < 128; i++) {
			if (i == 9 || i == 18 || i == 27)
				continue;
			ixp2000_reg_write(IXP2000_MSF_RBUF_ELEMENT_DONE, i);
		}
	} else if (size_bits == IXP2400_RX_MODE_RBUF_SIZE_128) {
		for (i = 1; i < 64; i++) {
			if (i == 4 || i == 9 || i == 13)
				continue;
			ixp2000_reg_write(IXP2000_MSF_RBUF_ELEMENT_DONE, i);
		}
	} else if (size_bits == IXP2400_RX_MODE_RBUF_SIZE_256) {
		for (i = 1; i < 32; i++) {
			if (i == 2 || i == 4 || i == 6)
				continue;
			ixp2000_reg_write(IXP2000_MSF_RBUF_ELEMENT_DONE, i);
		}
	}
}