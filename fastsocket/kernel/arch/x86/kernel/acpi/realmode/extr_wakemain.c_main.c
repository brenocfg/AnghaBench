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
struct TYPE_2__ {int real_magic; int realmode_flags; int /*<<< orphan*/  video_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  probe_cards (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_morse (char*) ; 
 int /*<<< orphan*/  set_mode (int /*<<< orphan*/ ) ; 
 TYPE_1__ wakeup_header ; 

void main(void)
{
	/* Kill machine if structures are wrong */
	if (wakeup_header.real_magic != 0x12345678)
		while (1);

	if (wakeup_header.realmode_flags & 4)
		send_morse("...-");

	if (wakeup_header.realmode_flags & 1)
		asm volatile("lcallw   $0xc000,$3");

	if (wakeup_header.realmode_flags & 2) {
		/* Need to call BIOS */
		probe_cards(0);
		set_mode(wakeup_header.video_mode);
	}
}