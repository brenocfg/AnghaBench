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
struct intel_encoder {int dummy; } ;
struct intel_crt {TYPE_2__* connector; } ;
struct TYPE_3__ {int /*<<< orphan*/  dpms; } ;
struct TYPE_4__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_crt_set_dpms (struct intel_encoder*,int /*<<< orphan*/ ) ; 
 struct intel_crt* intel_encoder_to_crt (struct intel_encoder*) ; 

__attribute__((used)) static void intel_enable_crt(struct intel_encoder *encoder)
{
	struct intel_crt *crt = intel_encoder_to_crt(encoder);

	intel_crt_set_dpms(encoder, crt->connector->base.dpms);
}