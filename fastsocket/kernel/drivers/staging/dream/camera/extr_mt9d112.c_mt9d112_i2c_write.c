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
typedef  scalar_t__ int32_t ;
typedef  enum mt9d112_width { ____Placeholder_mt9d112_width } mt9d112_width ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  BYTE_LEN 129 
 int /*<<< orphan*/  CDBG (char*,unsigned short,unsigned short) ; 
 scalar_t__ EIO ; 
#define  WORD_LEN 128 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mt9d112_i2c_txdata (unsigned short,unsigned char*,int) ; 

__attribute__((used)) static int32_t mt9d112_i2c_write(unsigned short saddr,
	unsigned short waddr, unsigned short wdata, enum mt9d112_width width)
{
	int32_t rc = -EIO;
	unsigned char buf[4];

	memset(buf, 0, sizeof(buf));
	switch (width) {
	case WORD_LEN: {
		buf[0] = (waddr & 0xFF00)>>8;
		buf[1] = (waddr & 0x00FF);
		buf[2] = (wdata & 0xFF00)>>8;
		buf[3] = (wdata & 0x00FF);

		rc = mt9d112_i2c_txdata(saddr, buf, 4);
	}
		break;

	case BYTE_LEN: {
		buf[0] = waddr;
		buf[1] = wdata;
		rc = mt9d112_i2c_txdata(saddr, buf, 2);
	}
		break;

	default:
		break;
	}

	if (rc < 0)
		CDBG(
		"i2c_write failed, addr = 0x%x, val = 0x%x!\n",
		waddr, wdata);

	return rc;
}