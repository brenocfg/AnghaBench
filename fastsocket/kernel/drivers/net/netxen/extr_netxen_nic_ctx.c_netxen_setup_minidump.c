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
typedef  int /*<<< orphan*/  u32 ;
struct netxen_minidump_template_hdr {int dummy; } ;
struct TYPE_4__ {int fw_supports_md; int md_template_size; int /*<<< orphan*/ * md_template; scalar_t__ md_enabled; int /*<<< orphan*/ * md_capture_buff; int /*<<< orphan*/  md_capture_mask; } ;
struct netxen_adapter {TYPE_2__ mdump; TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NX_DUMP_MASK_DEF ; 
 int /*<<< orphan*/  NX_MD_SUPPORT_MAJOR ; 
 int /*<<< orphan*/  NX_MD_SUPPORT_MINOR ; 
 int /*<<< orphan*/  NX_MD_SUPPORT_SUBVERSION ; 
 int NX_RCODE_CMD_INVALID ; 
 int NX_RCODE_CMD_NOT_IMPL ; 
 int /*<<< orphan*/  __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ netxen_check_template_checksum (struct netxen_adapter*) ; 
 int netxen_get_minidump_template (struct netxen_adapter*) ; 
 int netxen_get_minidump_template_size (struct netxen_adapter*) ; 

int
netxen_setup_minidump(struct netxen_adapter *adapter)
{
	int err = 0, i;
	u32 *template, *tmp_buf;
	struct netxen_minidump_template_hdr *hdr;
	err = netxen_get_minidump_template_size(adapter);
	if (err) {
		adapter->mdump.fw_supports_md = 0;
		if ((err == NX_RCODE_CMD_INVALID) ||
			(err == NX_RCODE_CMD_NOT_IMPL)) {
			dev_info(&adapter->pdev->dev,
				"Flashed firmware version does not support minidump, "
				"minimum version required is [ %u.%u.%u ].\n ",
				NX_MD_SUPPORT_MAJOR, NX_MD_SUPPORT_MINOR,
				NX_MD_SUPPORT_SUBVERSION);
		}
		return err;
	}

	if (!adapter->mdump.md_template_size) {
		dev_err(&adapter->pdev->dev, "Error : Invalid template size "
		",should be non-zero.\n");
		return -EIO;
	}
	adapter->mdump.md_template =
		kmalloc(adapter->mdump.md_template_size, GFP_KERNEL);

	if (!adapter->mdump.md_template) {
		dev_err(&adapter->pdev->dev, "Unable to allocate memory "
			"for minidump template.\n");
		return -ENOMEM;
	}

	err = netxen_get_minidump_template(adapter);
	if (err) {
		if (err == NX_RCODE_CMD_NOT_IMPL)
			adapter->mdump.fw_supports_md = 0;
		goto free_template;
	}

	if (netxen_check_template_checksum(adapter)) {
		dev_err(&adapter->pdev->dev, "Minidump template checksum Error\n");
		err = -EIO;
		goto free_template;
	}

	adapter->mdump.md_capture_mask = NX_DUMP_MASK_DEF;
	tmp_buf = (u32 *) adapter->mdump.md_template;
	template = (u32 *) adapter->mdump.md_template;
	for (i = 0; i < adapter->mdump.md_template_size/sizeof(u32); i++)
		*template++ = __le32_to_cpu(*tmp_buf++);
	hdr = (struct netxen_minidump_template_hdr *)
				adapter->mdump.md_template;
	adapter->mdump.md_capture_buff = NULL;
	adapter->mdump.fw_supports_md = 1;
	adapter->mdump.md_enabled = 0;

	return err;

free_template:
	kfree(adapter->mdump.md_template);
	adapter->mdump.md_template = NULL;
	return err;
}