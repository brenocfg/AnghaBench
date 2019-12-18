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
struct hdsp {scalar_t__ io_type; int firmware_rev; int /*<<< orphan*/  dds_value; } ;

/* Variables and functions */
 scalar_t__ H9632 ; 
 int /*<<< orphan*/  HDSP_freqReg ; 
 int /*<<< orphan*/  HDSP_resetPointer ; 
 int /*<<< orphan*/  hdsp_write (struct hdsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdsp_reset_hw_pointer(struct hdsp *hdsp)
{
	hdsp_write (hdsp, HDSP_resetPointer, 0);
	if (hdsp->io_type == H9632 && hdsp->firmware_rev >= 152)
		/* HDSP_resetPointer = HDSP_freqReg, which is strange and
		 * requires (?) to write again DDS value after a reset pointer
		 * (at least, it works like this) */
		hdsp_write (hdsp, HDSP_freqReg, hdsp->dds_value);
}