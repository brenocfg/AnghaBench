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
typedef  int /*<<< orphan*/  rarch_sinc_resampler_t ;

/* Variables and functions */
 double M_PI ; 
 double lanzcos_window_function (double) ; 
 double sinc (double) ; 

__attribute__((used)) static void sinc_init_table_lanczos(rarch_sinc_resampler_t *resamp, double cutoff,
      float *phase_table, int phases, int taps, bool calculate_delta)
{
   int i, j;
   double    window_mod = lanzcos_window_function(0.0); /* Need to normalize w(0) to 1.0. */
   int           stride = calculate_delta ? 2 : 1;
   double     sidelobes = taps / 2.0;

   for (i = 0; i < phases; i++)
   {
      for (j = 0; j < taps; j++)
      {
         double sinc_phase;
         float val;
         int               n = j * phases + i;
         double window_phase = (double)n / (phases * taps); /* [0, 1). */
         window_phase        = 2.0 * window_phase - 1.0; /* [-1, 1) */
         sinc_phase          = sidelobes * window_phase;
         val                 = cutoff * sinc(M_PI * sinc_phase * cutoff) *
            lanzcos_window_function(window_phase) / window_mod;
         phase_table[i * stride * taps + j] = val;
      }
   }

   if (calculate_delta)
   {
      int phase;
      int p;

      for (p = 0; p < phases - 1; p++)
      {
         for (j = 0; j < taps; j++)
         {
            float delta = phase_table[(p + 1) * stride * taps + j] -
               phase_table[p * stride * taps + j];
            phase_table[(p * stride + 1) * taps + j] = delta;
         }
      }

      phase = phases - 1;
      for (j = 0; j < taps; j++)
      {
         float val, delta;
         double sinc_phase;
         int n               = j * phases + (phase + 1);
         double window_phase = (double)n / (phases * taps); /* (0, 1]. */
         window_phase        = 2.0 * window_phase - 1.0; /* (-1, 1] */
         sinc_phase          = sidelobes * window_phase;

         val                 = cutoff * sinc(M_PI * sinc_phase * cutoff) *
            lanzcos_window_function(window_phase) / window_mod;
         delta = (val - phase_table[phase * stride * taps + j]);
         phase_table[(phase * stride + 1) * taps + j] = delta;
      }
   }
}