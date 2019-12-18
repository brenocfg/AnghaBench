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
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct snd_emu10k1 {TYPE_1__ silent_page; } ;

/* Variables and functions */
 int UNIT_PAGES ; 
 int /*<<< orphan*/  __set_ptb_entry (struct snd_emu10k1*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_silent_ptb(struct snd_emu10k1 *emu, int page)
{
	int i;
	page *= UNIT_PAGES;
	for (i = 0; i < UNIT_PAGES; i++, page++)
		/* do not increment ptr */
		__set_ptb_entry(emu, page, emu->silent_page.addr);
}