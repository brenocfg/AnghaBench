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
struct firmware {int dummy; } ;
struct b43_request_fw_context {int /*<<< orphan*/  fw_load_complete; struct firmware const* blob; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void b43_fw_cb(const struct firmware *firmware, void *context)
{
	struct b43_request_fw_context *ctx = context;

	ctx->blob = firmware;
	complete(&ctx->fw_load_complete);
}