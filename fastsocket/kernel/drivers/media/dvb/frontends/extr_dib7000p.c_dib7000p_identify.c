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
struct dib7000p_state {int /*<<< orphan*/  i2c_addr; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int dib7000p_read_word (struct dib7000p_state*,int) ; 
 int /*<<< orphan*/  dprintk (char*,int,...) ; 

__attribute__((used)) static int dib7000p_identify(struct dib7000p_state *st)
{
	u16 value;
	dprintk( "checking demod on I2C address: %d (%x)",
		st->i2c_addr, st->i2c_addr);

	if ((value = dib7000p_read_word(st, 768)) != 0x01b3) {
		dprintk( "wrong Vendor ID (read=0x%x)",value);
		return -EREMOTEIO;
	}

	if ((value = dib7000p_read_word(st, 769)) != 0x4000) {
		dprintk( "wrong Device ID (%x)",value);
		return -EREMOTEIO;
	}

	return 0;
}