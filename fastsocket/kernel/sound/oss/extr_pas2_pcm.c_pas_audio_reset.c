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
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int pas_read (int) ; 
 int /*<<< orphan*/  pas_write (int,int) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static void pas_audio_reset(int dev)
{
	DEB(printk("pas2_pcm.c: static void pas_audio_reset(void)\n"));

	pas_write(pas_read(0xF8A) & ~0x40, 0xF8A);	/* Disable PCM */
}