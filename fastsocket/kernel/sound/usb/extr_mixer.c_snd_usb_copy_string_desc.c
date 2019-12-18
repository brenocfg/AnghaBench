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
struct mixer_build {TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int usb_string (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static int snd_usb_copy_string_desc(struct mixer_build *state, int index, char *buf, int maxlen)
{
	int len = usb_string(state->chip->dev, index, buf, maxlen - 1);
	buf[len] = 0;
	return len;
}