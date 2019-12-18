#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {struct device* next; } ;
struct TYPE_5__ {struct device* dev; } ;
struct TYPE_4__ {int c_lflag; } ;

/* Variables and functions */
 int ECHO ; 
 int ICANON ; 
 int ISIG ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  TCSANOW ; 
 TYPE_3__ devices ; 
 TYPE_1__ orig_term ; 
 int /*<<< orphan*/  reset_device (struct device*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void cleanup_devices(void)
{
	struct device *dev;

	for (dev = devices.dev; dev; dev = dev->next)
		reset_device(dev);

	/* If we saved off the original terminal settings, restore them now. */
	if (orig_term.c_lflag & (ISIG|ICANON|ECHO))
		tcsetattr(STDIN_FILENO, TCSANOW, &orig_term);
}