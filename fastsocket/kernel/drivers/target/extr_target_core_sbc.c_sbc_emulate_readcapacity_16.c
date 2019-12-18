#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int block_size; scalar_t__ emulate_tpws; scalar_t__ emulate_tpu; } ;
struct se_device {TYPE_2__ dev_attrib; TYPE_1__* transport; } ;
struct se_cmd {int /*<<< orphan*/  data_length; struct se_device* se_dev; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {unsigned long long (* get_blocks ) (struct se_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GOOD ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 unsigned long long stub1 (struct se_device*) ; 
 int /*<<< orphan*/  target_complete_cmd (struct se_cmd*,int /*<<< orphan*/ ) ; 
 unsigned char* transport_kmap_data_sg (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_kunmap_data_sg (struct se_cmd*) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static sense_reason_t
sbc_emulate_readcapacity_16(struct se_cmd *cmd)
{
	struct se_device *dev = cmd->se_dev;
	unsigned char *rbuf;
	unsigned char buf[32];
	unsigned long long blocks = dev->transport->get_blocks(dev);

	memset(buf, 0, sizeof(buf));
	buf[0] = (blocks >> 56) & 0xff;
	buf[1] = (blocks >> 48) & 0xff;
	buf[2] = (blocks >> 40) & 0xff;
	buf[3] = (blocks >> 32) & 0xff;
	buf[4] = (blocks >> 24) & 0xff;
	buf[5] = (blocks >> 16) & 0xff;
	buf[6] = (blocks >> 8) & 0xff;
	buf[7] = blocks & 0xff;
	buf[8] = (dev->dev_attrib.block_size >> 24) & 0xff;
	buf[9] = (dev->dev_attrib.block_size >> 16) & 0xff;
	buf[10] = (dev->dev_attrib.block_size >> 8) & 0xff;
	buf[11] = dev->dev_attrib.block_size & 0xff;
	/*
	 * Set Thin Provisioning Enable bit following sbc3r22 in section
	 * READ CAPACITY (16) byte 14 if emulate_tpu or emulate_tpws is enabled.
	 */
	if (dev->dev_attrib.emulate_tpu || dev->dev_attrib.emulate_tpws)
		buf[14] = 0x80;

	rbuf = transport_kmap_data_sg(cmd);
	if (rbuf) {
		memcpy(rbuf, buf, min_t(u32, sizeof(buf), cmd->data_length));
		transport_kunmap_data_sg(cmd);
	}

	target_complete_cmd(cmd, GOOD);
	return 0;
}