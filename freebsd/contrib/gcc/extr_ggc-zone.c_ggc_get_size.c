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
struct small_page_entry {int dummy; } ;
struct page_entry {scalar_t__ large_p; scalar_t__ pch_p; } ;
struct large_page_entry {size_t bytes; } ;
typedef  int /*<<< orphan*/  alloc_type ;
struct TYPE_2__ {char const* page; int bytes; int /*<<< orphan*/  alloc_bits; } ;

/* Variables and functions */
 int BYTES_PER_ALLOC_BIT ; 
 TYPE_1__ pch_zone ; 
 size_t zone_find_object_size (struct small_page_entry*,void const*) ; 
 struct page_entry* zone_get_object_page (void const*) ; 
 size_t zone_object_size_1 (int /*<<< orphan*/ ,size_t,size_t,size_t) ; 

size_t
ggc_get_size (const void *p)
{
  struct page_entry *page;
  const char *ptr = (const char *) p;

  page = zone_get_object_page (p);

  if (page->pch_p)
    {
      size_t alloc_word, alloc_bit, offset, max_size;
      offset = (ptr - pch_zone.page) / BYTES_PER_ALLOC_BIT + 1;
      alloc_word = offset / (8 * sizeof (alloc_type));
      alloc_bit = offset % (8 * sizeof (alloc_type));
      max_size = pch_zone.bytes - (ptr - pch_zone.page);
      return zone_object_size_1 (pch_zone.alloc_bits, alloc_word, alloc_bit,
				 max_size);
    }

  if (page->large_p)
    return ((struct large_page_entry *)page)->bytes;
  else
    return zone_find_object_size ((struct small_page_entry *) page, p);
}