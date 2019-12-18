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
typedef  int uint16_t ;
struct snd_usb_caiaqdev {int /*<<< orphan*/  input_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASCHINE_PAD (unsigned int) ; 
 unsigned int MASCHINE_PADS ; 
 int be16_to_cpu (unsigned char const) ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_usb_caiaq_maschine_dispatch(struct snd_usb_caiaqdev *dev,
					const unsigned char *buf,
					unsigned int len)
{
	unsigned int i, pad_id;
	uint16_t pressure;

	for (i = 0; i < MASCHINE_PADS; i++) {
		pressure = be16_to_cpu(buf[i * 2] << 8 | buf[(i * 2) + 1]);
		pad_id = pressure >> 12;

		input_report_abs(dev->input_dev, MASCHINE_PAD(pad_id), pressure & 0xfff);
	}

	input_sync(dev->input_dev);
}