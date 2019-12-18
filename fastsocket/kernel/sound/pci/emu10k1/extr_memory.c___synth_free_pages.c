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
struct snd_emu10k1 {int /*<<< orphan*/ ** page_ptr_table; scalar_t__* page_addr_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 

__attribute__((used)) static void __synth_free_pages(struct snd_emu10k1 *emu, int first_page,
			       int last_page)
{
	int page;

	for (page = first_page; page <= last_page; page++) {
		free_page((unsigned long)emu->page_ptr_table[page]);
		emu->page_addr_table[page] = 0;
		emu->page_ptr_table[page] = NULL;
	}
}