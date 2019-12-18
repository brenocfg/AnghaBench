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
struct sscape_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_CTRL ; 
 int /*<<< orphan*/  PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void host_close(struct sscape_info *devc)
{
	outb((0x03), PORT(HOST_CTRL));	/* Put the board to the MIDI mode */
}