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
struct idset {int num_ssid; int num_id; int /*<<< orphan*/ * bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  __BITOPS_WORDS (int) ; 
 unsigned long min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void idset_add_set(struct idset *to, struct idset *from)
{
	unsigned long i, len;

	len = min(__BITOPS_WORDS(to->num_ssid * to->num_id),
		  __BITOPS_WORDS(from->num_ssid * from->num_id));
	for (i = 0; i < len ; i++)
		to->bitmap[i] |= from->bitmap[i];
}