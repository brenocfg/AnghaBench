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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct zone {int /*<<< orphan*/  wait_table_bits; int /*<<< orphan*/ * wait_table; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 size_t hash_long (unsigned long,int /*<<< orphan*/ ) ; 
 struct zone* page_zone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (void*) ; 

wait_queue_head_t *bit_waitqueue(void *word, int bit)
{
	const int shift = BITS_PER_LONG == 32 ? 5 : 6;
	const struct zone *zone = page_zone(virt_to_page(word));
	unsigned long val = (unsigned long)word << shift | bit;

	return &zone->wait_table[hash_long(val, zone->wait_table_bits)];
}