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
struct gx_font_cache_entry_t {int /*<<< orphan*/  font; struct gx_font_cache_entry_t* next; } ;

/* Variables and functions */
 struct gx_font_cache_entry_t* fonts ; 
 int /*<<< orphan*/  vcos_free (struct gx_font_cache_entry_t*) ; 
 int /*<<< orphan*/  vgft_font_term (int /*<<< orphan*/ *) ; 

void gx_font_cache_flush(void)
{
   while (fonts != NULL)
   {
      struct gx_font_cache_entry_t *next = fonts->next;
      vgft_font_term(&fonts->font);
      vcos_free(fonts);
      fonts = next;
   }
}