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
typedef  int u32 ;
struct r8180_priv {int rf_chip; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int* QUALITY_MAP ; 
#define  RFCHIPID_GCT 132 
#define  RFCHIPID_INTERSIL 131 
#define  RFCHIPID_MAXIM 130 
#define  RFCHIPID_PHILIPS 129 
#define  RFCHIPID_RFMD 128 
 int* STRENGTH_MAP ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 

void rtl8180_RSSI_calc(struct net_device *dev, u8 *rssi, u8 *qual)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);
	u32 temp;
	u32 temp2;
	u32 temp3;
	u32 lsb;
	u32 q;
	u32 orig_qual;
	u8  _rssi;

	q = *qual;
	orig_qual = *qual;
	_rssi = 0; // avoid gcc complains..

	if (q <= 0x4e) {
		temp = QUALITY_MAP[q];
	} else {
		if( q & 0x80 ) {
			temp = 0x32;
		} else {
			temp = 1;
		}
	}

	*qual = temp;
	temp2 = *rssi;

	switch(priv->rf_chip){
	case RFCHIPID_RFMD:
		lsb = temp2 & 1;
		temp2 &= 0x7e;
		if ( !lsb || !(temp2 <= 0x3c) ) {
			temp2 = 0x64;
		} else {
			temp2 = 100 * temp2 / 0x3c;
		}
		*rssi = temp2 & 0xff;
		_rssi = temp2 & 0xff;
		break;
	case RFCHIPID_INTERSIL:
		lsb = temp2;
		temp2 &= 0xfffffffe;
		temp2 *= 251;
		temp3 = temp2;
		temp2 <<= 6;
		temp3 += temp2;
		temp3 <<= 1;
		temp2 = 0x4950df;
		temp2 -= temp3;
		lsb &= 1;
		if ( temp2 <= 0x3e0000 ) {
			if ( temp2 < 0xffef0000 )
				temp2 = 0xffef0000;
		} else {
			temp2 = 0x3e0000;
		}
		if ( !lsb ) {
			temp2 -= 0xf0000;
		} else {
			temp2 += 0xf0000;
		}

		temp3 = 0x4d0000;
		temp3 -= temp2;
		temp3 *= 100;
		temp3 = temp3 / 0x6d;
		temp3 >>= 0x10;
		_rssi = temp3 & 0xff;
		*rssi = temp3 & 0xff;
		break;
	case RFCHIPID_GCT:
	        lsb = temp2 & 1;
		temp2 &= 0x7e;
		if ( ! lsb || !(temp2 <= 0x3c) ){
			temp2 = 0x64;
		} else {
			temp2 = (100 * temp2) / 0x3c;
		}
		*rssi = temp2 & 0xff;
		_rssi = temp2 & 0xff;
		break;
	case RFCHIPID_PHILIPS:
		if( orig_qual <= 0x4e ){
			_rssi = STRENGTH_MAP[orig_qual];
			*rssi = _rssi;
		} else {
			orig_qual -= 0x80;
			if ( !orig_qual ){
				_rssi = 1;
				*rssi = 1;
			} else {
				_rssi = 0x32;
				*rssi = 0x32;
			}
		}
		break;
	case RFCHIPID_MAXIM:
		lsb = temp2 & 1;
		temp2 &= 0x7e;
		temp2 >>= 1;
		temp2 += 0x42;
		if( lsb != 0 ){
			temp2 += 0xa;
		}
		*rssi = temp2 & 0xff;
		_rssi = temp2 & 0xff;
		break;
	}

	if ( _rssi < 0x64 ){
		if ( _rssi == 0 ) {
			*rssi = 1;
		}
	} else {
		*rssi = 0x64;
	}

	return;
}