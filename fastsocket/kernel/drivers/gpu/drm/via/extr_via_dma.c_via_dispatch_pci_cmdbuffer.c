#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_4__ {scalar_t__ pci_buf; } ;
typedef  TYPE_1__ drm_via_private_t ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  buf; } ;
typedef  TYPE_2__ drm_via_cmdbuffer_t ;

/* Variables and functions */
 scalar_t__ DRM_COPY_FROM_USER (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  VIA_PCI_BUF_SIZE ; 
 int via_parse_command_stream (struct drm_device*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int via_verify_command_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct drm_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int via_dispatch_pci_cmdbuffer(struct drm_device *dev,
				      drm_via_cmdbuffer_t *cmd)
{
	drm_via_private_t *dev_priv = dev->dev_private;
	int ret;

	if (cmd->size > VIA_PCI_BUF_SIZE)
		return -ENOMEM;
	if (DRM_COPY_FROM_USER(dev_priv->pci_buf, cmd->buf, cmd->size))
		return -EFAULT;

	if ((ret =
	     via_verify_command_stream((uint32_t *) dev_priv->pci_buf,
				       cmd->size, dev, 0))) {
		return ret;
	}

	ret =
	    via_parse_command_stream(dev, (const uint32_t *)dev_priv->pci_buf,
				     cmd->size);
	return ret;
}