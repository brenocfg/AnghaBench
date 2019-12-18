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
typedef  int u32 ;
struct TYPE_2__ {int rx_packets; int rx_errors; int tx_errors; int collisions; int rx_over_errors; int rx_crc_errors; int rx_frame_errors; int tx_aborted_errors; int tx_carrier_errors; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; scalar_t__ base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLAN_DEFERRED_TX ; 
 scalar_t__ TLAN_DIO_ADR ; 
 scalar_t__ TLAN_DIO_DATA ; 
 int /*<<< orphan*/  TLAN_EXCESSCOL_FRMS ; 
 int /*<<< orphan*/  TLAN_GOOD_RX_FRMS ; 
 int /*<<< orphan*/  TLAN_GOOD_TX_FRMS ; 
 int /*<<< orphan*/  TLAN_MULTICOL_FRMS ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void TLan_ReadAndClearStats( struct net_device *dev, int record )
{
	u32		tx_good, tx_under;
	u32		rx_good, rx_over;
	u32		def_tx, crc, code;
	u32		multi_col, single_col;
	u32		excess_col, late_col, loss;

	outw( TLAN_GOOD_TX_FRMS, dev->base_addr + TLAN_DIO_ADR );
	tx_good  = inb( dev->base_addr + TLAN_DIO_DATA );
	tx_good += inb( dev->base_addr + TLAN_DIO_DATA + 1 ) << 8;
	tx_good += inb( dev->base_addr + TLAN_DIO_DATA + 2 ) << 16;
	tx_under = inb( dev->base_addr + TLAN_DIO_DATA + 3 );

	outw( TLAN_GOOD_RX_FRMS, dev->base_addr + TLAN_DIO_ADR );
	rx_good  = inb( dev->base_addr + TLAN_DIO_DATA );
	rx_good += inb( dev->base_addr + TLAN_DIO_DATA + 1 ) << 8;
	rx_good += inb( dev->base_addr + TLAN_DIO_DATA + 2 ) << 16;
	rx_over  = inb( dev->base_addr + TLAN_DIO_DATA + 3 );

	outw( TLAN_DEFERRED_TX, dev->base_addr + TLAN_DIO_ADR );
	def_tx  = inb( dev->base_addr + TLAN_DIO_DATA );
	def_tx += inb( dev->base_addr + TLAN_DIO_DATA + 1 ) << 8;
	crc     = inb( dev->base_addr + TLAN_DIO_DATA + 2 );
	code    = inb( dev->base_addr + TLAN_DIO_DATA + 3 );

	outw( TLAN_MULTICOL_FRMS, dev->base_addr + TLAN_DIO_ADR );
	multi_col   = inb( dev->base_addr + TLAN_DIO_DATA );
	multi_col  += inb( dev->base_addr + TLAN_DIO_DATA + 1 ) << 8;
	single_col  = inb( dev->base_addr + TLAN_DIO_DATA + 2 );
	single_col += inb( dev->base_addr + TLAN_DIO_DATA + 3 ) << 8;

	outw( TLAN_EXCESSCOL_FRMS, dev->base_addr + TLAN_DIO_ADR );
	excess_col = inb( dev->base_addr + TLAN_DIO_DATA );
	late_col   = inb( dev->base_addr + TLAN_DIO_DATA + 1 );
	loss       = inb( dev->base_addr + TLAN_DIO_DATA + 2 );

	if ( record ) {
		dev->stats.rx_packets += rx_good;
		dev->stats.rx_errors  += rx_over + crc + code;
		dev->stats.tx_packets += tx_good;
		dev->stats.tx_errors  += tx_under + loss;
		dev->stats.collisions += multi_col + single_col + excess_col + late_col;

		dev->stats.rx_over_errors    += rx_over;
		dev->stats.rx_crc_errors     += crc;
		dev->stats.rx_frame_errors   += code;

		dev->stats.tx_aborted_errors += tx_under;
		dev->stats.tx_carrier_errors += loss;
	}

}