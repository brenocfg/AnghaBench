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
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_DDI (struct drm_device*) ; 
 int PORT_A ; 
 int PORT_E ; 
 int /*<<< orphan*/  intel_prepare_ddi_buffers (struct drm_device*,int,int) ; 

void intel_prepare_ddi(struct drm_device *dev)
{
	int port;

	if (!HAS_DDI(dev))
		return;

	for (port = PORT_A; port < PORT_E; port++)
		intel_prepare_ddi_buffers(dev, port, false);

	/* DDI E is the suggested one to work in FDI mode, so program is as such
	 * by default. It will have to be re-programmed in case a digital DP
	 * output will be detected on it
	 */
	intel_prepare_ddi_buffers(dev, PORT_E, true);
}