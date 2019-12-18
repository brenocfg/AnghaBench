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
 int SIL164_9_HTPLG ; 
 int /*<<< orphan*/  SIL164_REG9 ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int /*<<< orphan*/  sil164_readb (struct intel_dvo_device*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static enum drm_connector_status sil164_detect(struct intel_dvo_device *dvo)
{
	uint8_t reg9;

	sil164_readb(dvo, SIL164_REG9, &reg9);

	if (reg9 & SIL164_9_HTPLG)
		return connector_status_connected;
	else
		return connector_status_disconnected;
}