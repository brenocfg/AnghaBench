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
struct firmware_priv {int /*<<< orphan*/  completion; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_STATUS_ABORT ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
fw_load_abort(struct firmware_priv *fw_priv)
{
	set_bit(FW_STATUS_ABORT, &fw_priv->status);
	wmb();
	complete(&fw_priv->completion);
}