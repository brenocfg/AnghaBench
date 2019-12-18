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
typedef  int uint8_t ;
struct intel_dvo_device {int dummy; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int CH7xxx_CDET_DVI ; 
 int /*<<< orphan*/  CH7xxx_CONNECTION_DETECT ; 
 int /*<<< orphan*/  CH7xxx_PM ; 
 int CH7xxx_PM_DVIL ; 
 int CH7xxx_PM_DVIP ; 
 int CH7xxx_PM_FPD ; 
 int /*<<< orphan*/  ch7xxx_readb (struct intel_dvo_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ch7xxx_writeb (struct intel_dvo_device*,int /*<<< orphan*/ ,int) ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 

__attribute__((used)) static enum drm_connector_status ch7xxx_detect(struct intel_dvo_device *dvo)
{
	uint8_t cdet, orig_pm, pm;

	ch7xxx_readb(dvo, CH7xxx_PM, &orig_pm);

	pm = orig_pm;
	pm &= ~CH7xxx_PM_FPD;
	pm |= CH7xxx_PM_DVIL | CH7xxx_PM_DVIP;

	ch7xxx_writeb(dvo, CH7xxx_PM, pm);

	ch7xxx_readb(dvo, CH7xxx_CONNECTION_DETECT, &cdet);

	ch7xxx_writeb(dvo, CH7xxx_PM, orig_pm);

	if (cdet & CH7xxx_CDET_DVI)
		return connector_status_connected;
	return connector_status_disconnected;
}