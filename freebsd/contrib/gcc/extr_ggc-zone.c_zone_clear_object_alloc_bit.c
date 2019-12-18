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
struct small_page_entry {long* alloc_bits; } ;

/* Variables and functions */
 unsigned int zone_get_object_alloc_bit (void const*) ; 
 unsigned int zone_get_object_alloc_word (void const*) ; 

__attribute__((used)) static inline void
zone_clear_object_alloc_bit (struct small_page_entry *page,
			     const void *object)
{
  unsigned int start_word = zone_get_object_alloc_word (object);
  unsigned int start_bit = zone_get_object_alloc_bit (object);

  /* Would xor be quicker?  */
  page->alloc_bits[start_word] &= ~(1L << start_bit);
}