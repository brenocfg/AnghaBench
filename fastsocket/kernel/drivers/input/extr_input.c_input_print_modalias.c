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
struct TYPE_2__ {int bustype; int vendor; int product; int version; } ;
struct input_dev {int /*<<< orphan*/  swbit; int /*<<< orphan*/  ffbit; int /*<<< orphan*/  sndbit; int /*<<< orphan*/  ledbit; int /*<<< orphan*/  mscbit; int /*<<< orphan*/  absbit; int /*<<< orphan*/  relbit; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MAX ; 
 int /*<<< orphan*/  EV_MAX ; 
 int /*<<< orphan*/  FF_MAX ; 
 int /*<<< orphan*/  KEY_MAX ; 
 int /*<<< orphan*/  KEY_MIN_INTERESTING ; 
 int /*<<< orphan*/  LED_MAX ; 
 int /*<<< orphan*/  MSC_MAX ; 
 int /*<<< orphan*/  REL_MAX ; 
 int /*<<< orphan*/  SND_MAX ; 
 int /*<<< orphan*/  SW_MAX ; 
 scalar_t__ input_print_modalias_bits (char*,int,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (int,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int input_print_modalias(char *buf, int size, struct input_dev *id,
				int add_cr)
{
	int len;

	len = snprintf(buf, max(size, 0),
		       "input:b%04Xv%04Xp%04Xe%04X-",
		       id->id.bustype, id->id.vendor,
		       id->id.product, id->id.version);

	len += input_print_modalias_bits(buf + len, size - len,
				'e', id->evbit, 0, EV_MAX);
	len += input_print_modalias_bits(buf + len, size - len,
				'k', id->keybit, KEY_MIN_INTERESTING, KEY_MAX);
	len += input_print_modalias_bits(buf + len, size - len,
				'r', id->relbit, 0, REL_MAX);
	len += input_print_modalias_bits(buf + len, size - len,
				'a', id->absbit, 0, ABS_MAX);
	len += input_print_modalias_bits(buf + len, size - len,
				'm', id->mscbit, 0, MSC_MAX);
	len += input_print_modalias_bits(buf + len, size - len,
				'l', id->ledbit, 0, LED_MAX);
	len += input_print_modalias_bits(buf + len, size - len,
				's', id->sndbit, 0, SND_MAX);
	len += input_print_modalias_bits(buf + len, size - len,
				'f', id->ffbit, 0, FF_MAX);
	len += input_print_modalias_bits(buf + len, size - len,
				'w', id->swbit, 0, SW_MAX);

	if (add_cr)
		len += snprintf(buf + len, max(size - len, 0), "\n");

	return len;
}