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
struct eq_gain {int dummy; } ;
struct eq_data {int block_size; int /*<<< orphan*/  filter; int /*<<< orphan*/  fft; } ;
typedef  int /*<<< orphan*/  fft_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fft_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fft_new (unsigned int) ; 
 int /*<<< orphan*/  fft_process_forward (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*,int) ; 
 int /*<<< orphan*/  fft_process_inverse (int /*<<< orphan*/ *,float*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,float) ; 
 int /*<<< orphan*/  free (float*) ; 
 int /*<<< orphan*/  gains_cmp ; 
 int /*<<< orphan*/  generate_response (int /*<<< orphan*/ ,struct eq_gain*,unsigned int,int) ; 
 double kaiser_window_function (double,double) ; 
 int /*<<< orphan*/  qsort (struct eq_gain*,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void create_filter(struct eq_data *eq, unsigned size_log2,
      struct eq_gain *gains, unsigned num_gains, double beta, const char *filter_path)
{
   int i;
   int half_block_size = eq->block_size >> 1;
   double window_mod = 1.0 / kaiser_window_function(0.0, beta);

   fft_t *fft = fft_new(size_log2);
   float *time_filter = (float*)calloc(eq->block_size * 2 + 1, sizeof(*time_filter));
   if (!fft || !time_filter)
      goto end;

   /* Make sure bands are in correct order. */
   qsort(gains, num_gains, sizeof(*gains), gains_cmp);

   /* Compute desired filter response. */
   generate_response(eq->filter, gains, num_gains, half_block_size);

   /* Get equivalent time-domain filter. */
   fft_process_inverse(fft, time_filter, eq->filter, 1);

   /* ifftshift() to create the correct linear phase filter.
    * The filter response was designed with zero phase, which
    * won't work unless we compensate
    * for the repeating property of the FFT here
    * by flipping left and right blocks. */
   for (i = 0; i < half_block_size; i++)
   {
      float tmp = time_filter[i + half_block_size];
      time_filter[i + half_block_size] = time_filter[i];
      time_filter[i] = tmp;
   }

   /* Apply a window to smooth out the frequency repsonse. */
   for (i = 0; i < (int)eq->block_size; i++)
   {
      /* Kaiser window. */
      double phase = (double)i / eq->block_size;
      phase = 2.0 * (phase - 0.5);
      time_filter[i] *= window_mod * kaiser_window_function(phase, beta);
   }

   /* Debugging. */
   if (filter_path)
   {
      FILE *file = fopen(filter_path, "w");
      if (file)
      {
         for (i = 0; i < (int)eq->block_size - 1; i++)
            fprintf(file, "%.8f\n", time_filter[i + 1]);
         fclose(file);
      }
   }

   /* Padded FFT to create our FFT filter.
    * Make our even-length filter odd by discarding the first coefficient.
    * For some interesting reason, this allows us to design an odd-length linear phase filter.
    */
   fft_process_forward(eq->fft, eq->filter, time_filter + 1, 1);

end:
   fft_free(fft);
   free(time_filter);
}