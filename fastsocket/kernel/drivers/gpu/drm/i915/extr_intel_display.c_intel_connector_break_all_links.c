#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * encoder; int /*<<< orphan*/  dpms; } ;
struct intel_connector {TYPE_3__* encoder; TYPE_1__ base; } ;
struct TYPE_5__ {int /*<<< orphan*/ * crtc; } ;
struct TYPE_6__ {int connectors_active; TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 

__attribute__((used)) static void
intel_connector_break_all_links(struct intel_connector *connector)
{
	connector->base.dpms = DRM_MODE_DPMS_OFF;
	connector->base.encoder = NULL;
	connector->encoder->connectors_active = false;
	connector->encoder->base.crtc = NULL;
}