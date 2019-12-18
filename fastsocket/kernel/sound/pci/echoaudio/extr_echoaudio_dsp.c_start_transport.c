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
typedef  int /*<<< orphan*/  u32 ;
struct echoaudio {TYPE_1__* comm_page; int /*<<< orphan*/  active_mask; } ;
struct TYPE_2__ {int cmd_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_ACT (char*) ; 
 int /*<<< orphan*/  DSP_VC_START_TRANSFER ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  clear_handshake (struct echoaudio*) ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_vector (struct echoaudio*,int /*<<< orphan*/ ) ; 
 scalar_t__ wait_handshake (struct echoaudio*) ; 

__attribute__((used)) static int start_transport(struct echoaudio *chip, u32 channel_mask,
			   u32 cyclic_mask)
{
	DE_ACT(("start_transport %x\n", channel_mask));

	if (wait_handshake(chip))
		return -EIO;

	chip->comm_page->cmd_start |= cpu_to_le32(channel_mask);

	if (chip->comm_page->cmd_start) {
		clear_handshake(chip);
		send_vector(chip, DSP_VC_START_TRANSFER);
		if (wait_handshake(chip))
			return -EIO;
		/* Keep track of which pipes are transporting */
		chip->active_mask |= channel_mask;
		chip->comm_page->cmd_start = 0;
		return 0;
	}

	DE_ACT(("start_transport: No pipes to start!\n"));
	return -EINVAL;
}