#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {float* decoder_matrix; scalar_t__ saturation; scalar_t__ hue; scalar_t__ gamma; scalar_t__ fringing; scalar_t__ artifacts; int /*<<< orphan*/  palette; scalar_t__ contrast; scalar_t__ brightness; } ;
typedef  TYPE_1__ md_ntsc_setup_t ;
struct TYPE_9__ {float contrast; float artifacts; float fringing; float* to_rgb; scalar_t__ brightness; scalar_t__* to_float; } ;
typedef  TYPE_2__ init_t ;

/* Variables and functions */
 float PI ; 
 int /*<<< orphan*/  ROTATE_IQ (float,float,float,float) ; 
 scalar_t__ STD_HUE_CONDITION (TYPE_1__ const*) ; 
 float artifacts_max ; 
 int artifacts_mid ; 
 int burst_count ; 
 scalar_t__ cos (float) ; 
 float* default_decoder ; 
 float default_palette_contrast ; 
 float ext_decoder_hue ; 
 float fringing_max ; 
 int fringing_mid ; 
 int gamma_size ; 
 int /*<<< orphan*/  init_filters (TYPE_2__*,TYPE_1__ const*) ; 
 scalar_t__ pow (int,float const) ; 
 scalar_t__ rgb_offset ; 
 float rgb_unit ; 
 scalar_t__ sin (float) ; 
 float std_decoder_hue ; 

__attribute__((used)) static void init( init_t* impl, md_ntsc_setup_t const* setup )
{
  impl->brightness = (float) setup->brightness * (0.5f * rgb_unit) + rgb_offset;
  impl->contrast   = (float) setup->contrast   * (0.5f * rgb_unit) + rgb_unit;
  #ifdef default_palette_contrast
    if ( !setup->palette )
      impl->contrast *= default_palette_contrast;
  #endif

  impl->artifacts = (float) setup->artifacts;
  if ( impl->artifacts > 0 )
    impl->artifacts *= artifacts_max - artifacts_mid;
  impl->artifacts = impl->artifacts * artifacts_mid + artifacts_mid;

  impl->fringing = (float) setup->fringing;
  if ( impl->fringing > 0 )
    impl->fringing *= fringing_max - fringing_mid;
  impl->fringing = impl->fringing * fringing_mid + fringing_mid;

  init_filters( impl, setup );

  /* generate gamma table */
  if ( gamma_size > 1 )
  {
    float const to_float = 1.0f / (gamma_size - (gamma_size > 1));
    float const gamma = 1.1333f - (float) setup->gamma * 0.5f;
    /* match common PC's 2.2 gamma to TV's 2.65 gamma */
    int i;
    for ( i = 0; i < gamma_size; i++ )
      impl->to_float [i] =
          (float) pow( i * to_float, gamma ) * impl->contrast + impl->brightness;
  }

  /* setup decoder matricies */
  {
    float hue = (float) setup->hue * PI + PI / 180 * ext_decoder_hue;
    float sat = (float) setup->saturation + 1;
    float const* decoder = setup->decoder_matrix;
    if ( !decoder )
    {
      decoder = default_decoder;
      if ( STD_HUE_CONDITION( setup ) )
        hue += PI / 180 * (std_decoder_hue - ext_decoder_hue);
    }

    {
      float s = (float) sin( hue ) * sat;
      float c = (float) cos( hue ) * sat;
      float* out = impl->to_rgb;
      int n;

      n = burst_count;
      do
      {
        float const* in = decoder;
        int n = 3;
        do
        {
          float i = *in++;
          float q = *in++;
          *out++ = i * c - q * s;
          *out++ = i * s + q * c;
        }
        while ( --n );
        if ( burst_count <= 1 )
          break;
        ROTATE_IQ( s, c, 0.866025f, -0.5f ); /* +120 degrees */
      }
      while ( --n );
    }
  }
}