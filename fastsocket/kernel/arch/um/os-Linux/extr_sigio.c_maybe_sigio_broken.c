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

/* Variables and functions */
 int /*<<< orphan*/  isatty (int) ; 
 scalar_t__ pty_close_sigio ; 
 scalar_t__ pty_output_sigio ; 
 int /*<<< orphan*/  sigio_broken (int,int) ; 

void maybe_sigio_broken(int fd, int read)
{
	if (!isatty(fd))
		return;

	if ((read || pty_output_sigio) && (!read || pty_close_sigio))
		return;

	sigio_broken(fd, read);
}