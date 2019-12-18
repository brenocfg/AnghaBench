#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ bleed; scalar_t__ resolution; scalar_t__ sharpness; } ;
typedef  TYPE_1__ sms_ntsc_setup_t ;
struct TYPE_6__ {float* kernel; } ;
typedef  TYPE_2__ init_t ;

/* Variables and functions */
 scalar_t__ LUMA_CUTOFF ; 
 float const PI ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ cos (float const) ; 
 scalar_t__ exp (int) ; 
 int kernel_half ; 
 int kernel_size ; 
 scalar_t__ pow (float const,float const) ; 
 float rescale_in ; 
 int rescale_out ; 

__attribute__((used)) static void init_filters( init_t* impl, sms_ntsc_setup_t const* setup )
{
#if rescale_out > 1
  float kernels [kernel_size * 2];
#else
  float* const kernels = impl->kernel;
#endif

  /* generate luma (y) filter using sinc kernel */
  {
    /* sinc with rolloff (dsf) */
    float const rolloff = 1 + (float) setup->sharpness * (float) 0.032;
    float const maxh = 32;
    float const pow_a_n = (float) pow( rolloff, maxh );
    float sum;
    int i;
    /* quadratic mapping to reduce negative (blurring) range */
    float to_angle = (float) setup->resolution + 1;
    to_angle = PI / maxh * (float) LUMA_CUTOFF * (to_angle * to_angle + 1);
    
    kernels [kernel_size * 3 / 2] = maxh; /* default center value */
    for ( i = 0; i < kernel_half * 2 + 1; i++ )
    {
      int x = i - kernel_half;
      float angle = x * to_angle;
      /* instability occurs at center point with rolloff very close to 1.0 */
      if ( x || pow_a_n > (float) 1.056 || pow_a_n < (float) 0.981 )
      {
        float rolloff_cos_a = rolloff * (float) cos( angle );
        float num = 1 - rolloff_cos_a -
            pow_a_n * (float) cos( maxh * angle ) +
            pow_a_n * rolloff * (float) cos( (maxh - 1) * angle );
        float den = 1 - rolloff_cos_a - rolloff_cos_a + rolloff * rolloff;
        float dsf = num / den;
        kernels [kernel_size * 3 / 2 - kernel_half + i] = dsf - (float) 0.5;
      }
    }
    
    /* apply blackman window and find sum */
    sum = 0;
    for ( i = 0; i < kernel_half * 2 + 1; i++ )
    {
      float x = PI * 2 / (kernel_half * 2) * i;
      float blackman = 0.42f - 0.5f * (float) cos( x ) + 0.08f * (float) cos( x * 2 );
      sum += (kernels [kernel_size * 3 / 2 - kernel_half + i] *= blackman);
    }
    
    /* normalize kernel */
    sum = 1.0f / sum;
    for ( i = 0; i < kernel_half * 2 + 1; i++ )
    {
      int x = kernel_size * 3 / 2 - kernel_half + i;
      kernels [x] *= sum;
      assert( kernels [x] == kernels [x] ); /* catch numerical instability */
    }
  }

  /* generate chroma (iq) filter using gaussian kernel */
  {
    float const cutoff_factor = -0.03125f;
    float cutoff = (float) setup->bleed;
    int i;
    
    if ( cutoff < 0 )
    {
      /* keep extreme value accessible only near upper end of scale (1.0) */
      cutoff *= cutoff;
      cutoff *= cutoff;
      cutoff *= cutoff;
      cutoff *= -30.0f / 0.65f;
    }
    cutoff = cutoff_factor - 0.65f * cutoff_factor * cutoff;
    
    for ( i = -kernel_half; i <= kernel_half; i++ )
      kernels [kernel_size / 2 + i] = (float) exp( i * i * cutoff );
    
    /* normalize even and odd phases separately */
    for ( i = 0; i < 2; i++ )
    {
      float sum = 0;
      int x;
      for ( x = i; x < kernel_size; x += 2 )
        sum += kernels [x];
      
      sum = 1.0f / sum;
      for ( x = i; x < kernel_size; x += 2 )
      {
        kernels [x] *= sum;
        assert( kernels [x] == kernels [x] ); /* catch numerical instability */
      }
    }
  }
  
  /*
  printf( "luma:\n" );
  for ( i = kernel_size; i < kernel_size * 2; i++ )
    printf( "%f\n", kernels [i] );
  printf( "chroma:\n" );
  for ( i = 0; i < kernel_size; i++ )
    printf( "%f\n", kernels [i] );
  */
  
  /* generate linear rescale kernels */
  #if rescale_out > 1
  {
    float weight = 1.0f;
    float* out = impl->kernel;
    int n = rescale_out;
    do
    {
      float remain = 0;
      int i;
      weight -= 1.0f / rescale_in;
      for ( i = 0; i < kernel_size * 2; i++ )
      {
        float cur = kernels [i];
        float m = cur * weight;
        *out++ = m + remain;
        remain = cur - m;
      }
    }
    while ( --n );
  }
  #endif
}