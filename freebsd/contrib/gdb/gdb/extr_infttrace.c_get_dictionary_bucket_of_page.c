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
struct TYPE_2__ {int page_size; } ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int MEMORY_PAGE_DICTIONARY_BUCKET_COUNT ; 
 TYPE_1__ memory_page_dictionary ; 

__attribute__((used)) static int
get_dictionary_bucket_of_page (CORE_ADDR page_start)
{
  int hash;

  hash = (page_start / memory_page_dictionary.page_size);
  hash = hash % MEMORY_PAGE_DICTIONARY_BUCKET_COUNT;

  return hash;
}