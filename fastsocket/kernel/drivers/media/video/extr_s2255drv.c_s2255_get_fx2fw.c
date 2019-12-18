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
struct s2255_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S2255_VR_FW ; 
 int /*<<< orphan*/  S2255_VR_IN ; 
 int /*<<< orphan*/  dprintk (int,char*,unsigned char,...) ; 
 int s2255_vendor_req (struct s2255_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s2255_get_fx2fw(struct s2255_dev *dev)
{
	int fw;
	int ret;
	unsigned char transBuffer[64];
	ret = s2255_vendor_req(dev, S2255_VR_FW, 0, 0, transBuffer, 2,
			       S2255_VR_IN);
	if (ret < 0)
		dprintk(2, "get fw error: %x\n", ret);
	fw = transBuffer[0] + (transBuffer[1] << 8);
	dprintk(2, "Get FW %x %x\n", transBuffer[0], transBuffer[1]);
	return fw;
}