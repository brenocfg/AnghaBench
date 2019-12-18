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
typedef  int u16 ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int REQUEST_SET_CLOCK ; 
 int dib0700_ctrl_wr (struct dvb_usb_device*,int*,int) ; 

__attribute__((used)) static int dib0700_set_clock(struct dvb_usb_device *d, u8 en_pll,
	u8 pll_src, u8 pll_range, u8 clock_gpio3, u16 pll_prediv,
	u16 pll_loopdiv, u16 free_div, u16 dsuScaler)
{
	u8 b[10];
	b[0] = REQUEST_SET_CLOCK;
	b[1] = (en_pll << 7) | (pll_src << 6) | (pll_range << 5) | (clock_gpio3 << 4);
	b[2] = (pll_prediv >> 8)  & 0xff; // MSB
	b[3] =  pll_prediv        & 0xff; // LSB
	b[4] = (pll_loopdiv >> 8) & 0xff; // MSB
	b[5] =  pll_loopdiv       & 0xff; // LSB
	b[6] = (free_div >> 8)    & 0xff; // MSB
	b[7] =  free_div          & 0xff; // LSB
	b[8] = (dsuScaler >> 8)   & 0xff; // MSB
	b[9] =  dsuScaler         & 0xff; // LSB

	return dib0700_ctrl_wr(d, b, 10);
}