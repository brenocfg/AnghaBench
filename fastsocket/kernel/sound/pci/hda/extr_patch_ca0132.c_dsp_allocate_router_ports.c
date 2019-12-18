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
typedef  unsigned int u8 ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 unsigned int MEM_CONNID_DSP ; 
 int /*<<< orphan*/  VENDOR_CHIPIO_PORT_ALLOC_CONFIG_SET ; 
 int /*<<< orphan*/  VENDOR_CHIPIO_PORT_ALLOC_GET ; 
 int /*<<< orphan*/  VENDOR_CHIPIO_PORT_ALLOC_SET ; 
 int /*<<< orphan*/  VENDOR_CHIPIO_STATUS ; 
 int /*<<< orphan*/  WIDGET_CHIP_CTRL ; 
 int chipio_send (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int dsp_allocate_router_ports(struct hda_codec *codec,
				     unsigned int num_chans,
				     unsigned int ports_per_channel,
				     unsigned int start_device,
				     unsigned int *port_map)
{
	int status = 0;
	int res;
	u8 val;

	status = chipio_send(codec, VENDOR_CHIPIO_STATUS, 0);
	if (status < 0)
		return status;

	val = start_device << 6;
	val |= (ports_per_channel - 1) << 4;
	val |= num_chans - 1;

	snd_hda_codec_write(codec, WIDGET_CHIP_CTRL, 0,
			    VENDOR_CHIPIO_PORT_ALLOC_CONFIG_SET,
			    val);

	snd_hda_codec_write(codec, WIDGET_CHIP_CTRL, 0,
			    VENDOR_CHIPIO_PORT_ALLOC_SET,
			    MEM_CONNID_DSP);

	status = chipio_send(codec, VENDOR_CHIPIO_STATUS, 0);
	if (status < 0)
		return status;

	res = snd_hda_codec_read(codec, WIDGET_CHIP_CTRL, 0,
				VENDOR_CHIPIO_PORT_ALLOC_GET, 0);

	*port_map = res;

	return (res < 0) ? res : 0;
}