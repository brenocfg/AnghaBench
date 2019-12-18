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
struct intel_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 int /*<<< orphan*/  intel_crt_set_dpms (struct intel_encoder*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_disable_crt(struct intel_encoder *encoder)
{
	intel_crt_set_dpms(encoder, DRM_MODE_DPMS_OFF);
}