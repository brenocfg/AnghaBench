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
struct iir_data {float b0; float b1; float b2; float a0; float a1; float a2; } ;
typedef  enum IIRFilter { ____Placeholder_IIRFilter } IIRFilter ;

/* Variables and functions */
#define  APF 139 
#define  BBOOST 138 
#define  BPCSGF 137 
#define  BPZPGF 136 
#define  HPF 135 
#define  HSH 134 
#define  LPF 133 
#define  LSH 132 
 double M_PI ; 
#define  NOTCH 131 
#define  PEQ 130 
#define  RIAA_CD 129 
#define  RIAA_phono 128 
 float cos (double) ; 
 double exp (double) ; 
 double log (double) ; 
 int /*<<< orphan*/  make_poly_from_roots (double const*,int,float*) ; 
 int /*<<< orphan*/  pow (double,int) ; 
 float sin (double) ; 
 double sqr (double) ; 
 double sqrt (double) ; 

__attribute__((used)) static void iir_filter_init(struct iir_data *iir,
      float sample_rate, float freq, float qual, float gain, enum IIRFilter filter_type)
{
	double omega = 2.0 * M_PI * freq / sample_rate;
   double cs    = cos(omega);
   double sn    = sin(omega);
   double a1pha = sn / (2.0 * qual);
   double A     = exp(log(10.0) * gain / 40.0);
   double beta  = sqrt(A + A);

   float b0     = 0.0, b1 = 0.0, b2 = 0.0, a0 = 0.0, a1 = 0.0, a2 = 0.0;

   /* Set up filter coefficients according to type */
   switch (filter_type)
   {
      case LPF:
         b0 =  (1.0 - cs) / 2.0;
         b1 =   1.0 - cs ;
         b2 =  (1.0 - cs) / 2.0;
         a0 =   1.0 + a1pha;
         a1 =  -2.0 * cs;
         a2 =   1.0 - a1pha;
         break;
      case HPF:
         b0 =  (1.0 + cs) / 2.0;
         b1 = -(1.0 + cs);
         b2 =  (1.0 + cs) / 2.0;
         a0 =   1.0 + a1pha;
         a1 =  -2.0 * cs;
         a2 =   1.0 - a1pha;
         break;
      case APF:
         b0 =  1.0 - a1pha;
         b1 = -2.0 * cs;
         b2 =  1.0 + a1pha;
         a0 =  1.0 + a1pha;
         a1 = -2.0 * cs;
         a2 =  1.0 - a1pha;
         break;
      case BPZPGF:
         b0 =  a1pha;
         b1 =  0.0;
         b2 = -a1pha;
         a0 =  1.0 + a1pha;
         a1 = -2.0 * cs;
         a2 =  1.0 - a1pha;
         break;
      case BPCSGF:
         b0 =  sn / 2.0;
         b1 =  0.0;
         b2 = -sn / 2.0;
         a0 =  1.0 + a1pha;
         a1 = -2.0 * cs;
         a2 =  1.0 - a1pha;
         break;
      case NOTCH:
         b0 =  1.0;
         b1 = -2.0 * cs;
         b2 =  1.0;
         a0 =  1.0 + a1pha;
         a1 = -2.0 * cs;
         a2 =  1.0 - a1pha;
         break;
      case RIAA_phono: /* http://www.dsprelated.com/showmessage/73300/3.php */
      {
         double y, b_re, a_re, b_im, a_im, g;
         float b[3], a[3];

         if ((int)sample_rate == 44100)
         {
            static const double zeros[] = {-0.2014898, 0.9233820};
            static const double poles[] = {0.7083149, 0.9924091};
            make_poly_from_roots(zeros, 2, b);
            make_poly_from_roots(poles, 2, a);
         }
         else if ((int)sample_rate == 48000)
         {
            static const double zeros[] = {-0.1766069, 0.9321590};
            static const double poles[] = {0.7396325, 0.9931330};
            make_poly_from_roots(zeros, 2, b);
            make_poly_from_roots(poles, 2, a);
         }
         else if ((int)sample_rate == 88200)
         {
            static const double zeros[] = {-0.1168735, 0.9648312};
            static const double poles[] = {0.8590646, 0.9964002};
            make_poly_from_roots(zeros, 2, b);
            make_poly_from_roots(poles, 2, a);
         }
         else if ((int)sample_rate == 96000)
         {
            static const double zeros[] = {-0.1141486, 0.9676817};
            static const double poles[] = {0.8699137, 0.9966946};
            make_poly_from_roots(zeros, 2, b);
            make_poly_from_roots(poles, 2, a);
         }

         b0    = b[0];
         b1    = b[1];
         b2    = b[2];
         a0    = a[0];
         a1    = a[1];
         a2    = a[2];

         /* Normalise to 0dB at 1kHz (Thanks to Glenn Davis) */
         y     = 2.0 * M_PI * 1000.0 / sample_rate;
         b_re  = b0 + b1 * cos(-y) + b2 * cos(-2.0 * y);
         a_re  = a0 + a1 * cos(-y) + a2 * cos(-2.0 * y);
         b_im  = b1 * sin(-y) + b2 * sin(-2.0 * y);
         a_im  = a1 * sin(-y) + a2 * sin(-2.0 * y);
         g     = 1.0 / sqrt((sqr(b_re) + sqr(b_im)) / (sqr(a_re) + sqr(a_im)));
         b0   *= g; b1 *= g; b2 *= g;
         break;
      }
      case PEQ:
         b0 =  1.0 + a1pha * A;
         b1 = -2.0 * cs;
         b2 =  1.0 - a1pha * A;
         a0 =  1.0 + a1pha / A;
         a1 = -2.0 * cs;
         a2 =  1.0 - a1pha / A;
         break;
      case BBOOST:
         beta = sqrt((A * A + 1) / 1.0 - (pow((A - 1), 2)));
         b0 = A * ((A + 1) - (A - 1) * cs + beta * sn);
         b1 = 2 * A * ((A - 1) - (A + 1) * cs);
         b2 = A * ((A + 1) - (A - 1) * cs - beta * sn);
         a0 = ((A + 1) + (A - 1) * cs + beta * sn);
         a1 = -2 * ((A - 1) + (A + 1) * cs);
         a2 = (A + 1) + (A - 1) * cs - beta * sn;
         break;
      case LSH:
         b0 = A * ((A + 1) - (A - 1) * cs + beta * sn);
         b1 = 2 * A * ((A - 1) - (A + 1) * cs);
         b2 = A * ((A + 1) - (A - 1) * cs - beta * sn);
         a0 = (A + 1) + (A - 1) * cs + beta * sn;
         a1 = -2 * ((A - 1) + (A + 1) * cs);
         a2 = (A + 1) + (A - 1) * cs - beta * sn;
         break;
      case RIAA_CD:
         omega = 2.0 * M_PI * 5283.0 / sample_rate;
         cs = cos(omega);
         sn = sin(omega);
         a1pha = sn / (2.0 * 0.4845);
         A = exp(log(10.0) * -9.477 / 40.0);
         beta = sqrt(A + A);
         (void)a1pha;
      case HSH:
         b0 = A * ((A + 1.0) + (A - 1.0) * cs + beta * sn);
         b1 = -2.0 * A * ((A - 1.0) + (A + 1.0) * cs);
         b2 = A * ((A + 1.0) + (A - 1.0) * cs - beta * sn);
         a0 = (A + 1.0) - (A - 1.0) * cs + beta * sn;
         a1 = 2.0 * ((A - 1.0) - (A + 1.0) * cs);
         a2 = (A + 1.0) - (A - 1.0) * cs - beta * sn;
         break;
      default:
         break;
   }

   iir->b0 = b0;
   iir->b1 = b1;
   iir->b2 = b2;
   iir->a0 = a0;
   iir->a1 = a1;
   iir->a2 = a2;
}