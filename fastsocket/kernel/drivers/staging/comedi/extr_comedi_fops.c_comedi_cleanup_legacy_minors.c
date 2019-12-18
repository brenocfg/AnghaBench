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
 int /*<<< orphan*/  comedi_free_board_minor (unsigned int) ; 
 unsigned int comedi_num_legacy_minors ; 

__attribute__((used)) static void comedi_cleanup_legacy_minors(void)
{
	unsigned i;

	for (i = 0; i < comedi_num_legacy_minors; i++)
		comedi_free_board_minor(i);
}