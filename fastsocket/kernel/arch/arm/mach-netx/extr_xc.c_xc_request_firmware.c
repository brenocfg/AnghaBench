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
struct xc {int no; int /*<<< orphan*/  version; int /*<<< orphan*/  type; int /*<<< orphan*/  dev; } ;
struct fw_header {int magic; TYPE_1__* fw_desc; int /*<<< orphan*/  version; int /*<<< orphan*/  type; } ;
struct firmware {void* data; } ;
struct TYPE_2__ {int ofs; int size; int patch_ofs; unsigned int patch_entries; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ io_p2v (unsigned long) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,unsigned int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ xc_check_ptr (struct xc*,unsigned long,unsigned int) ; 
 int xc_patch (struct xc*,void const*,unsigned int) ; 

int xc_request_firmware(struct xc *x)
{
	int ret;
	char name[16];
	const struct firmware *fw;
	struct fw_header *head;
	unsigned int size;
	int i;
	const void *src;
	unsigned long dst;

	sprintf(name, "xc%d.bin", x->no);

	ret = request_firmware(&fw, name, x->dev);

	if (ret < 0) {
		dev_err(x->dev, "request_firmware failed\n");
		return ret;
	}

	head = (struct fw_header *)fw->data;
	if (head->magic != 0x4e657458) {
		if (head->magic == 0x5874654e) {
			dev_err(x->dev,
			    "firmware magic is 'XteN'. Endianess problems?\n");
			ret = -ENODEV;
			goto exit_release_firmware;
		}
		dev_err(x->dev, "unrecognized firmware magic 0x%08x\n",
			head->magic);
		ret = -ENODEV;
		goto exit_release_firmware;
	}

	x->type = head->type;
	x->version = head->version;

	ret = -EINVAL;

	for (i = 0; i < 3; i++) {
		src = fw->data + head->fw_desc[i].ofs;
		dst = *(unsigned int *)src;
		src += sizeof (unsigned int);
		size = head->fw_desc[i].size - sizeof (unsigned int);

		if (xc_check_ptr(x, dst, size))
			goto exit_release_firmware;

		memcpy((void *)io_p2v(dst), src, size);

		src = fw->data + head->fw_desc[i].patch_ofs;
		size = head->fw_desc[i].patch_entries;
		ret = xc_patch(x, src, size);
		if (ret < 0)
			goto exit_release_firmware;
	}

	ret = 0;

      exit_release_firmware:
	release_firmware(fw);

	return ret;
}