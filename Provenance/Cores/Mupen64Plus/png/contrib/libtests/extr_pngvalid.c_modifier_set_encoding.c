#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int current_gamma; int encoding_counter; int ngammas; int* gammas; unsigned int nencodings; TYPE_1__* encodings; TYPE_1__* current_encoding; scalar_t__ encoding_ignored; } ;
typedef  TYPE_2__ png_modifier ;
struct TYPE_4__ {int gamma; } ;

/* Variables and functions */

__attribute__((used)) static void
modifier_set_encoding(png_modifier *pm)
{
   /* Set the encoding to the one specified by the current encoding counter,
    * first clear out all the settings - this corresponds to an encoding_counter
    * of 0.
    */
   pm->current_gamma = 0;
   pm->current_encoding = 0;
   pm->encoding_ignored = 0; /* not ignored yet - happens in _ini functions. */

   /* Now, if required, set the gamma and encoding fields. */
   if (pm->encoding_counter > 0)
   {
      /* The gammas[] array is an array of screen gammas, not encoding gammas,
       * so we need the inverse:
       */
      if (pm->encoding_counter <= pm->ngammas)
         pm->current_gamma = 1/pm->gammas[pm->encoding_counter-1];

      else
      {
         unsigned int i = pm->encoding_counter - pm->ngammas;

         if (i >= pm->nencodings)
         {
            i %= pm->nencodings;
            pm->current_gamma = 1; /* Linear, only in the 16 bit case */
         }

         else
            pm->current_gamma = pm->encodings[i].gamma;

         pm->current_encoding = pm->encodings + i;
      }
   }
}