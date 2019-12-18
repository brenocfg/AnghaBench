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
struct TYPE_2__ {unsigned char* control; } ;
struct usb_line6_variax {int /*<<< orphan*/  dumpreq; TYPE_1__ model_data; } ;
struct usb_interface {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int line6_wait_dump (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sprintf (char*,char*,char*,unsigned int,unsigned int) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 struct usb_line6_variax* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static ssize_t variax_get_param_float(struct device *dev, char *buf, int param)
{
	/*
		We do our own floating point handling here since floats in the
		kernel are problematic for at least two reasons: - many distros
		are still shipped with binary kernels optimized for the ancient
		80386 without FPU
		- there isn't a printf("%f")
		  (see http://www.kernelthread.com/publications/faq/335.html)
	*/

	static const int BIAS = 0x7f;
	static const int OFFSET = 0xf;
	static const int PRECISION = 1000;

	int len = 0;
	unsigned part_int, part_frac;
	struct usb_interface *interface = to_usb_interface(dev);
	struct usb_line6_variax *variax = usb_get_intfdata(interface);
	const unsigned char *p = variax->model_data.control + param;
	int retval = line6_wait_dump(&variax->dumpreq, 0);
	if (retval < 0)
		return retval;

	if ((p[0] == 0) && (p[1] == 0) && (p[2] == 0))
		part_int = part_frac = 0;
	else {
		int exponent = (((p[0] & 0x7f) << 1) | (p[1] >> 7)) - BIAS;
		unsigned mantissa = (p[1] << 8) | p[2] | 0x8000;
		exponent -= OFFSET;

		if (exponent >= 0) {
			part_int = mantissa << exponent;
			part_frac = 0;
		} else {
			part_int = mantissa >> -exponent;
			part_frac = (mantissa << (32 + exponent)) & 0xffffffff;
		}

		part_frac = (part_frac / ((1UL << 31) / (PRECISION / 2 * 10)) + 5) / 10;
	}

	len += sprintf(buf + len, "%s%d.%03d\n", ((p[0] & 0x80) ? "-" : ""), part_int, part_frac);
	return len;
}