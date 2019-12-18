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

/* Variables and functions */

__attribute__((used)) static unsigned int cp210x_quantise_baudrate(unsigned int baud) {
	if      (baud <= 56)       baud = 0;
	else if (baud <= 300)      baud = 300;
	else if (baud <= 600)      baud = 600;
	else if (baud <= 1200)     baud = 1200;
	else if (baud <= 1800)     baud = 1800;
	else if (baud <= 2400)     baud = 2400;
	else if (baud <= 4000)     baud = 4000;
	else if (baud <= 4803)     baud = 4800;
	else if (baud <= 7207)     baud = 7200;
	else if (baud <= 9612)     baud = 9600;
	else if (baud <= 14428)    baud = 14400;
	else if (baud <= 16062)    baud = 16000;
	else if (baud <= 19250)    baud = 19200;
	else if (baud <= 28912)    baud = 28800;
	else if (baud <= 38601)    baud = 38400;
	else if (baud <= 51558)    baud = 51200;
	else if (baud <= 56280)    baud = 56000;
	else if (baud <= 58053)    baud = 57600;
	else if (baud <= 64111)    baud = 64000;
	else if (baud <= 77608)    baud = 76800;
	else if (baud <= 117028)   baud = 115200;
	else if (baud <= 129347)   baud = 128000;
	else if (baud <= 156868)   baud = 153600;
	else if (baud <= 237832)   baud = 230400;
	else if (baud <= 254234)   baud = 250000;
	else if (baud <= 273066)   baud = 256000;
	else if (baud <= 491520)   baud = 460800;
	else if (baud <= 567138)   baud = 500000;
	else if (baud <= 670254)   baud = 576000;
	else if (baud <= 1053257)  baud = 921600;
	else if (baud <= 1474560)  baud = 1228800;
	else if (baud <= 2457600)  baud = 1843200;
	else                       baud = 3686400;
	return baud;
}