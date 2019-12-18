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
struct hdsp {void* io_type; } ;

/* Variables and functions */
 void* Digiface ; 
 int EIO ; 
 int HDSP_DllError ; 
 int /*<<< orphan*/  HDSP_PROGRAM ; 
 int /*<<< orphan*/  HDSP_SHORT_WAIT ; 
 int /*<<< orphan*/  HDSP_S_LOAD ; 
 int /*<<< orphan*/  HDSP_VERSION_BIT ; 
 int /*<<< orphan*/  HDSP_control2Reg ; 
 int /*<<< orphan*/  HDSP_fifoData ; 
 int /*<<< orphan*/  HDSP_status2Register ; 
 int /*<<< orphan*/  HDSP_statusRegister ; 
 int HDSP_version1 ; 
 void* Multiface ; 
 scalar_t__ hdsp_fifo_wait (struct hdsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hdsp_read (struct hdsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdsp_write (struct hdsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdsp_get_iobox_version (struct hdsp *hdsp)
{
	if ((hdsp_read (hdsp, HDSP_statusRegister) & HDSP_DllError) != 0) {

		hdsp_write (hdsp, HDSP_control2Reg, HDSP_PROGRAM);
		hdsp_write (hdsp, HDSP_fifoData, 0);
		if (hdsp_fifo_wait (hdsp, 0, HDSP_SHORT_WAIT) < 0)
			return -EIO;

		hdsp_write (hdsp, HDSP_control2Reg, HDSP_S_LOAD);
		hdsp_write (hdsp, HDSP_fifoData, 0);

		if (hdsp_fifo_wait (hdsp, 0, HDSP_SHORT_WAIT)) {
			hdsp->io_type = Multiface;
			hdsp_write (hdsp, HDSP_control2Reg, HDSP_VERSION_BIT);
			hdsp_write (hdsp, HDSP_control2Reg, HDSP_S_LOAD);
			hdsp_fifo_wait (hdsp, 0, HDSP_SHORT_WAIT);
		} else {
			hdsp->io_type = Digiface;
		}
	} else {
		/* firmware was already loaded, get iobox type */
		if (hdsp_read(hdsp, HDSP_status2Register) & HDSP_version1)
			hdsp->io_type = Multiface;
		else
			hdsp->io_type = Digiface;
	}
	return 0;
}