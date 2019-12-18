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
typedef  int u16 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int HFA384X_DATA0_OFF ; 
 int HFA384X_DATA1_OFF ; 
 char HFA384X_INB (int) ; 
 int /*<<< orphan*/  HFA384X_INSW (int,void*,int) ; 

__attribute__((used)) static int hfa384x_from_bap(struct net_device *dev, u16 bap, void *buf,
			    int len)
{
	u16 d_off;
	u16 *pos;

	d_off = (bap == 1) ? HFA384X_DATA1_OFF : HFA384X_DATA0_OFF;
	pos = (u16 *) buf;

	if (len / 2)
		HFA384X_INSW(d_off, buf, len / 2);
	pos += len / 2;

	if (len & 1)
		*((char *) pos) = HFA384X_INB(d_off);

	return 0;
}