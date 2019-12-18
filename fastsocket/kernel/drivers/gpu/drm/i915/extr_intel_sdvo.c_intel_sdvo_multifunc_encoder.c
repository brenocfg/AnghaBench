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
struct TYPE_2__ {int /*<<< orphan*/  output_flags; } ;
struct intel_sdvo {TYPE_1__ caps; } ;

/* Variables and functions */
 int hweight16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
intel_sdvo_multifunc_encoder(struct intel_sdvo *intel_sdvo)
{
	/* Is there more than one type of output? */
	return hweight16(intel_sdvo->caps.output_flags) > 1;
}