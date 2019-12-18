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
struct myri10ge_priv {size_t sram_size; int fw_ver_major; int fw_ver_minor; int fw_ver_tiny; int adopted_rx_filter_bug; scalar_t__ sram; TYPE_1__* pdev; } ;
struct mcp_gen_header {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MCP_HEADER_PTR_OFFSET ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int,int,int) ; 
 int /*<<< orphan*/  kfree (struct mcp_gen_header*) ; 
 struct mcp_gen_header* kmalloc (size_t const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_fromio (struct mcp_gen_header*,scalar_t__,size_t const) ; 
 int myri10ge_validate_firmware (struct myri10ge_priv*,struct mcp_gen_header*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 size_t swab32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int myri10ge_adopt_running_firmware(struct myri10ge_priv *mgp)
{
	struct mcp_gen_header *hdr;
	struct device *dev = &mgp->pdev->dev;
	const size_t bytes = sizeof(struct mcp_gen_header);
	size_t hdr_offset;
	int status;

	/* find running firmware header */
	hdr_offset = swab32(readl(mgp->sram + MCP_HEADER_PTR_OFFSET));

	if ((hdr_offset & 3) || hdr_offset + sizeof(*hdr) > mgp->sram_size) {
		dev_err(dev, "Running firmware has bad header offset (%d)\n",
			(int)hdr_offset);
		return -EIO;
	}

	/* copy header of running firmware from SRAM to host memory to
	 * validate firmware */
	hdr = kmalloc(bytes, GFP_KERNEL);
	if (hdr == NULL) {
		dev_err(dev, "could not malloc firmware hdr\n");
		return -ENOMEM;
	}
	memcpy_fromio(hdr, mgp->sram + hdr_offset, bytes);
	status = myri10ge_validate_firmware(mgp, hdr);
	kfree(hdr);

	/* check to see if adopted firmware has bug where adopting
	 * it will cause broadcasts to be filtered unless the NIC
	 * is kept in ALLMULTI mode */
	if (mgp->fw_ver_major == 1 && mgp->fw_ver_minor == 4 &&
	    mgp->fw_ver_tiny >= 4 && mgp->fw_ver_tiny <= 11) {
		mgp->adopted_rx_filter_bug = 1;
		dev_warn(dev, "Adopting fw %d.%d.%d: "
			 "working around rx filter bug\n",
			 mgp->fw_ver_major, mgp->fw_ver_minor,
			 mgp->fw_ver_tiny);
	}
	return status;
}