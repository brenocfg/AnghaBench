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
 int TTS_WRITABLE ; 
 int /*<<< orphan*/  dtlk_port_tts ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int) ; 

__attribute__((used)) static int dtlk_writeable(void)
{
	/* TRACE_TEXT(" dtlk_writeable"); */
#ifdef TRACINGMORE
	printk(" dtlk_writeable=%u", (inb_p(dtlk_port_tts) & TTS_WRITABLE)!=0);
#endif
	return inb_p(dtlk_port_tts) & TTS_WRITABLE;
}