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
typedef  int /*<<< orphan*/  u8 ;
struct intel_sdvo {int dummy; } ;

/* Variables and functions */
 int intel_sdvo_read_response (struct intel_sdvo*,void*,int) ; 
 int /*<<< orphan*/  intel_sdvo_write_cmd (struct intel_sdvo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
intel_sdvo_get_value(struct intel_sdvo *intel_sdvo, u8 cmd, void *value, int len)
{
	if (!intel_sdvo_write_cmd(intel_sdvo, cmd, NULL, 0))
		return false;

	return intel_sdvo_read_response(intel_sdvo, value, len);
}