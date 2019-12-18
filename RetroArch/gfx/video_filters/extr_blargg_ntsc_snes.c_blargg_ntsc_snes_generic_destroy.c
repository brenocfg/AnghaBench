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
struct filter_data {struct filter_data* workers; struct filter_data* ntsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct filter_data*) ; 

__attribute__((used)) static void blargg_ntsc_snes_generic_destroy(void *data)
{
   struct filter_data *filt = (struct filter_data*)data;

   if (!filt)
      return;

   if(filt->ntsc)
      free(filt->ntsc);

   free(filt->workers);
   free(filt);
}