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
struct comedi_subdevice {int io_bits; } ;

/* Variables and functions */
 int BUF_A0 ; 
 int BUF_A1 ; 
 int BUF_B0 ; 
 int BUF_B1 ; 
 int BUF_C0 ; 
 int BUF_C1 ; 

__attribute__((used)) static int compute_buffer(int config, int devno, struct comedi_subdevice *s)
{
	/* 1 in io_bits indicates output */
	if (s->io_bits & 0x0000ff) {
		if (devno == 0) {
			config |= BUF_A0;
		} else {
			config |= BUF_A1;
		}
	}
	if (s->io_bits & 0x00ff00) {
		if (devno == 0) {
			config |= BUF_B0;
		} else {
			config |= BUF_B1;
		}
	}
	if (s->io_bits & 0xff0000) {
		if (devno == 0) {
			config |= BUF_C0;
		} else {
			config |= BUF_C1;
		}
	}
	return config;
}