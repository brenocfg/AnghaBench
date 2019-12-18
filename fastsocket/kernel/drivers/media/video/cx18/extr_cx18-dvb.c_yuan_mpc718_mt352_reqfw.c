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
struct firmware {size_t size; } ;
struct cx18_stream {struct cx18* cx; } ;
struct cx18 {TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_ERR (char*,...) ; 
 int EILSEQ ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int yuan_mpc718_mt352_reqfw(struct cx18_stream *stream,
				   const struct firmware **fw)
{
	struct cx18 *cx = stream->cx;
	const char *fn = "dvb-cx18-mpc718-mt352.fw";
	int ret;

	ret = request_firmware(fw, fn, &cx->pci_dev->dev);
	if (ret)
		CX18_ERR("Unable to open firmware file %s\n", fn);
	else {
		size_t sz = (*fw)->size;
		if (sz < 2 || sz > 64 || (sz % 2) != 0) {
			CX18_ERR("Firmware %s has a bad size: %lu bytes\n",
				 fn, (unsigned long) sz);
			ret = -EILSEQ;
			release_firmware(*fw);
			*fw = NULL;
		}
	}

	if (ret) {
		CX18_ERR("The MPC718 board variant with the MT352 DVB-T"
			  "demodualtor will not work without it\n");
		CX18_ERR("Run 'linux/Documentation/dvb/get_dvb_firmware "
			  "mpc718' if you need the firmware\n");
	}
	return ret;
}