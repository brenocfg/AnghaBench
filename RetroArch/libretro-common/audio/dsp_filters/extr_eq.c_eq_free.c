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
struct eq_data {struct eq_data* filter; struct eq_data* fftblock; struct eq_data* block; struct eq_data* save; int /*<<< orphan*/  fft; } ;

/* Variables and functions */
 int /*<<< orphan*/  fft_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct eq_data*) ; 

__attribute__((used)) static void eq_free(void *data)
{
   struct eq_data *eq = (struct eq_data*)data;
   if (!eq)
      return;

   fft_free(eq->fft);
   free(eq->save);
   free(eq->block);
   free(eq->fftblock);
   free(eq->filter);
   free(eq);
}