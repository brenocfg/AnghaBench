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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ctr_free_pages (int) ; 
 int ctr_get_free_space () ; 

void ctr_request_free_pages(u32 pages)
{
   u32 free_pages = ctr_get_free_space() >> 12;
   if (pages > free_pages)
   {
      ctr_free_pages(pages - free_pages);
      free_pages = ctr_get_free_space() >> 12;
   }
}