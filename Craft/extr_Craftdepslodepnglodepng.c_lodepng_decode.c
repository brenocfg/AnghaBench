#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ colortype; int bitdepth; } ;
struct TYPE_11__ {int /*<<< orphan*/  fix_png; int /*<<< orphan*/  color_convert; } ;
struct TYPE_10__ {int /*<<< orphan*/  color; } ;
struct TYPE_12__ {int error; TYPE_2__ decoder; TYPE_1__ info_png; TYPE_4__ info_raw; } ;
typedef  TYPE_3__ LodePNGState ;

/* Variables and functions */
 scalar_t__ LCT_RGB ; 
 scalar_t__ LCT_RGBA ; 
 int /*<<< orphan*/  decodeGeneric (unsigned char**,unsigned int*,unsigned int*,TYPE_3__*,unsigned char const*,size_t) ; 
 int lodepng_color_mode_copy (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ lodepng_color_mode_equal (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int lodepng_convert (unsigned char*,unsigned char*,TYPE_4__*,int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lodepng_free (unsigned char*) ; 
 size_t lodepng_get_raw_size (unsigned int,unsigned int,TYPE_4__*) ; 
 scalar_t__ lodepng_malloc (size_t) ; 

unsigned lodepng_decode(unsigned char** out, unsigned* w, unsigned* h,
                        LodePNGState* state,
                        const unsigned char* in, size_t insize)
{
  *out = 0;
  decodeGeneric(out, w, h, state, in, insize);
  if(state->error) return state->error;
  if(!state->decoder.color_convert || lodepng_color_mode_equal(&state->info_raw, &state->info_png.color))
  {
    /*same color type, no copying or converting of data needed*/
    /*store the info_png color settings on the info_raw so that the info_raw still reflects what colortype
    the raw image has to the end user*/
    if(!state->decoder.color_convert)
    {
      state->error = lodepng_color_mode_copy(&state->info_raw, &state->info_png.color);
      if(state->error) return state->error;
    }
  }
  else
  {
    /*color conversion needed; sort of copy of the data*/
    unsigned char* data = *out;
    size_t outsize;

    /*TODO: check if this works according to the statement in the documentation: "The converter can convert
    from greyscale input color type, to 8-bit greyscale or greyscale with alpha"*/
    if(!(state->info_raw.colortype == LCT_RGB || state->info_raw.colortype == LCT_RGBA)
       && !(state->info_raw.bitdepth == 8))
    {
      return 56; /*unsupported color mode conversion*/
    }

    outsize = lodepng_get_raw_size(*w, *h, &state->info_raw);
    *out = (unsigned char*)lodepng_malloc(outsize);
    if(!(*out))
    {
      state->error = 83; /*alloc fail*/
    }
    else state->error = lodepng_convert(*out, data, &state->info_raw, &state->info_png.color, *w, *h, state->decoder.fix_png);
    lodepng_free(data);
  }
  return state->error;
}