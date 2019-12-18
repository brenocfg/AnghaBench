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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ TLAN_DIO_ADR ; 
 scalar_t__ TLAN_DIO_DATA ; 
 scalar_t__ TLAN_NET_SIO ; 
 int /*<<< orphan*/  TLAN_NET_SIO_ECLOK ; 
 int /*<<< orphan*/  TLAN_NET_SIO_EDATA ; 
 int /*<<< orphan*/  TLAN_NET_SIO_ETXEN ; 
 int /*<<< orphan*/  TLan_ClearBit (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ TLan_GetBit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TLan_SetBit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void TLan_EeReceiveByte( u16 io_base, u8 *data, int stop )
{
	u8  place;
	u16 sio;

	outw( TLAN_NET_SIO, io_base + TLAN_DIO_ADR );
	sio = io_base + TLAN_DIO_DATA + TLAN_NET_SIO;
	*data = 0;

	/* Assume clock is low, tx is enabled; */
	TLan_ClearBit( TLAN_NET_SIO_ETXEN, sio );
	for ( place = 0x80; place; place >>= 1 ) {
		TLan_SetBit( TLAN_NET_SIO_ECLOK, sio );
		if ( TLan_GetBit( TLAN_NET_SIO_EDATA, sio ) )
			*data |= place;
		TLan_ClearBit( TLAN_NET_SIO_ECLOK, sio );
	}

	TLan_SetBit( TLAN_NET_SIO_ETXEN, sio );
	if ( ! stop ) {
		TLan_ClearBit( TLAN_NET_SIO_EDATA, sio );	/* Ack = 0 */
		TLan_SetBit( TLAN_NET_SIO_ECLOK, sio );
		TLan_ClearBit( TLAN_NET_SIO_ECLOK, sio );
	} else {
		TLan_SetBit( TLAN_NET_SIO_EDATA, sio );		/* No ack = 1 (?) */
		TLan_SetBit( TLAN_NET_SIO_ECLOK, sio );
		TLan_ClearBit( TLAN_NET_SIO_ECLOK, sio );
		/* STOP, raise data while clock is high */
		TLan_ClearBit( TLAN_NET_SIO_EDATA, sio );
		TLan_SetBit( TLAN_NET_SIO_ECLOK, sio );
		TLan_SetBit( TLAN_NET_SIO_EDATA, sio );
	}

}