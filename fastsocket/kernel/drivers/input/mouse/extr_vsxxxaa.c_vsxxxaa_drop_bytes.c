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
struct vsxxxaa {int count; scalar_t__ buf; } ;

/* Variables and functions */
 scalar_t__ BUFLEN ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
vsxxxaa_drop_bytes (struct vsxxxaa *mouse, int num)
{
	if (num >= mouse->count)
		mouse->count = 0;
	else {
		memmove (mouse->buf, mouse->buf + num - 1, BUFLEN - num);
		mouse->count -= num;
	}
}