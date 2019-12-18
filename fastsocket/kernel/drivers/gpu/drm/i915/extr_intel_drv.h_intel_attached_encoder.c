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
struct intel_encoder {int dummy; } ;
struct drm_connector {int dummy; } ;
struct TYPE_2__ {struct intel_encoder* encoder; } ;

/* Variables and functions */
 TYPE_1__* to_intel_connector (struct drm_connector*) ; 

__attribute__((used)) static inline struct intel_encoder *intel_attached_encoder(struct drm_connector *connector)
{
	return to_intel_connector(connector)->encoder;
}