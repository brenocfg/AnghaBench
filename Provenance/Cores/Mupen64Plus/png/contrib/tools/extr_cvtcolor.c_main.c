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

/* Variables and functions */
 int /*<<< orphan*/  FE_TONEAREST ; 
 double YfromRGB (double,double,double) ; 
 double component (char const*,char const*,int) ; 
 int /*<<< orphan*/  fesetround (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int) ; 
 double linear_from_sRGB (double) ; 
 double nearbyint (double) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 double sRGB_from_linear (double) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage (char const*) ; 

int
main(int argc, const char **argv)
{
   const char *prog = *argv++;
   int to_linear = 0, to_gray = 0, to_color = 0;
   int channels = 0;
   double c[4];

   /* FE_TONEAREST is the IEEE754 round to nearest, preferring even, mode; i.e.
    * everything rounds to the nearest value except that '.5' rounds to the
    * nearest even value.
    */
   fesetround(FE_TONEAREST);

   c[3] = c[2] = c[1] = c[0] = 0;

   while (--argc > 0 && **argv == '-')
   {
      const char *arg = 1+*argv++;

      if (strcmp(arg, "sRGB") == 0)
         to_linear = 0;

      else if (strcmp(arg, "linear") == 0)
         to_linear = 1;

      else if (strcmp(arg, "gray") == 0)
         to_gray = 1, to_color = 0;

      else if (strcmp(arg, "color") == 0)
         to_gray = 0, to_color = 1;

      else
         usage(prog);
   }

   switch (argc)
   {
      default:
         usage(prog);
         break;

      case 4:
         c[3] = component(prog, argv[3], to_linear);
         ++channels;
      case 3:
         c[2] = component(prog, argv[2], to_linear);
         ++channels;
      case 2:
         c[1] = component(prog, argv[1], to_linear);
         ++channels;
      case 1:
         c[0] = component(prog, argv[0], to_linear);
         ++channels;
         break;
      }

   if (to_linear)
   {
      int i;
      int components = channels;

      if ((components & 1) == 0)
         --components;

      for (i=0; i<components; ++i) c[i] = linear_from_sRGB(c[i] / 255);
      if (components < channels)
         c[components] = c[components] / 255;
   }

   else
   {
      int i;
      for (i=0; i<4; ++i) c[i] /= 65535;

      if ((channels & 1) == 0)
      {
         double alpha = c[channels-1];

         if (alpha > 0)
            for (i=0; i<channels-1; ++i) c[i] /= alpha;
         else
            for (i=0; i<channels-1; ++i) c[i] = 1;
      }
   }

   if (to_gray)
   {
      if (channels < 3)
      {
         fprintf(stderr, "%s: too few channels (%d) for -gray\n",
            prog, channels);
         usage(prog);
      }

      c[0] = YfromRGB(c[0], c[1], c[2]);
      channels -= 2;
   }

   if (to_color)
   {
      if (channels > 2)
      {
         fprintf(stderr, "%s: too many channels (%d) for -color\n",
            prog, channels);
         usage(prog);
      }

      c[3] = c[1]; /* alpha, if present */
      c[2] = c[1] = c[0];
   }

   if (to_linear)
   {
      int i;
      if ((channels & 1) == 0)
      {
         double alpha = c[channels-1];
         for (i=0; i<channels-1; ++i) c[i] *= alpha;
      }

      for (i=0; i<channels; ++i) c[i] = nearbyint(c[i] * 65535);
   }

   else /* to sRGB */
   {
      int i = (channels+1)&~1;
      while (--i >= 0)
         c[i] = sRGB_from_linear(c[i]);

      for (i=0; i<channels; ++i) c[i] = nearbyint(c[i] * 255);
   }

   {
      int i;
      for (i=0; i<channels; ++i) printf(" %g", c[i]);
   }
   printf("\n");

   return 0;
}