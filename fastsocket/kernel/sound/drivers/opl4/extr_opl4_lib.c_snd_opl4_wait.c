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
struct snd_opl4 {int /*<<< orphan*/  fm_port; } ;

/* Variables and functions */
 int OPL4_STATUS_BUSY ; 
 int inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void inline snd_opl4_wait(struct snd_opl4 *opl4)
{
	int timeout = 10;
	while ((inb(opl4->fm_port) & OPL4_STATUS_BUSY) && --timeout > 0)
		;
}