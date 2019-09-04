#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int colored_done; int greybits_done; int numcolors_done; int sixteenbit_done; unsigned int key_r; unsigned int key_g; unsigned int key_b; unsigned int numcolors; unsigned int greybits; unsigned char* palette; scalar_t__ key; scalar_t__ colored; scalar_t__ alpha; scalar_t__ sixteenbit; } ;
struct TYPE_13__ {scalar_t__ colortype; int bitdepth; scalar_t__ palettesize; int /*<<< orphan*/ * palette; scalar_t__ key_defined; } ;
typedef  TYPE_1__ LodePNGColorMode ;
typedef  scalar_t__ LodePNGAutoConvert ;
typedef  TYPE_2__ ColorProfile ;

/* Variables and functions */
 scalar_t__ LAC_ALPHA ; 
 scalar_t__ LAC_AUTO_NO_NIBBLES ; 
 scalar_t__ LAC_AUTO_NO_NIBBLES_NO_PALETTE ; 
 scalar_t__ LAC_AUTO_NO_PALETTE ; 
 void* LCT_GREY ; 
 scalar_t__ LCT_GREY_ALPHA ; 
 scalar_t__ LCT_PALETTE ; 
 void* LCT_RGB ; 
 scalar_t__ LCT_RGBA ; 
 int /*<<< orphan*/  color_profile_cleanup (TYPE_2__*) ; 
 int /*<<< orphan*/  color_profile_init (TYPE_2__*,TYPE_1__ const*) ; 
 unsigned int get_color_profile (TYPE_2__*,unsigned char const*,unsigned int,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 unsigned int lodepng_palette_add (TYPE_1__*,unsigned char,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  lodepng_palette_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  setColorKeyFrom16bit (TYPE_1__*,unsigned int,unsigned int,unsigned int,int) ; 

unsigned lodepng_auto_choose_color(LodePNGColorMode* mode_out,
                                   const unsigned char* image, unsigned w, unsigned h,
                                   const LodePNGColorMode* mode_in,
                                   LodePNGAutoConvert auto_convert)
{
  ColorProfile profile;
  unsigned error = 0;
  int no_nibbles = auto_convert == LAC_AUTO_NO_NIBBLES || auto_convert == LAC_AUTO_NO_NIBBLES_NO_PALETTE;
  int no_palette = auto_convert == LAC_AUTO_NO_PALETTE || auto_convert == LAC_AUTO_NO_NIBBLES_NO_PALETTE;

  if(auto_convert == LAC_ALPHA)
  {
    if(mode_out->colortype != LCT_RGBA && mode_out->colortype != LCT_GREY_ALPHA) return 0;
  }

  color_profile_init(&profile, mode_in);
  if(auto_convert == LAC_ALPHA)
  {
    profile.colored_done = 1;
    profile.greybits_done = 1;
    profile.numcolors_done = 1;
    profile.sixteenbit_done = 1;
  }
  error = get_color_profile(&profile, image, w * h, mode_in, 0 /*fix_png*/);
  if(!error && auto_convert == LAC_ALPHA)
  {
    if(!profile.alpha)
    {
      mode_out->colortype = (mode_out->colortype == LCT_RGBA ? LCT_RGB : LCT_GREY);
      if(profile.key) setColorKeyFrom16bit(mode_out, profile.key_r, profile.key_g, profile.key_b, mode_out->bitdepth);
    }
  }
  else if(!error && auto_convert != LAC_ALPHA)
  {
    mode_out->key_defined = 0;

    if(profile.sixteenbit)
    {
      mode_out->bitdepth = 16;
      if(profile.alpha)
      {
        mode_out->colortype = profile.colored ? LCT_RGBA : LCT_GREY_ALPHA;
      }
      else
      {
        mode_out->colortype = profile.colored ? LCT_RGB : LCT_GREY;
        if(profile.key) setColorKeyFrom16bit(mode_out, profile.key_r, profile.key_g, profile.key_b, mode_out->bitdepth);
      }
    }
    else /*less than 16 bits per channel*/
    {
      /*don't add palette overhead if image hasn't got a lot of pixels*/
      unsigned n = profile.numcolors;
      int palette_ok = !no_palette && n <= 256 && (n * 2 < w * h);
      unsigned palettebits = n <= 2 ? 1 : (n <= 4 ? 2 : (n <= 16 ? 4 : 8));
      int grey_ok = !profile.colored && !profile.alpha; /*grey without alpha, with potentially low bits*/
      if(palette_ok || grey_ok)
      {
        if(!palette_ok || (grey_ok && profile.greybits <= palettebits))
        {
          unsigned grey = profile.key_r;
          mode_out->colortype = LCT_GREY;
          mode_out->bitdepth = profile.greybits;
          if(profile.key) setColorKeyFrom16bit(mode_out, grey, grey, grey, mode_out->bitdepth);
        }
        else
        {
          /*fill in the palette*/
          unsigned i;
          unsigned char* p = profile.palette;
          /*remove potential earlier palette*/
          lodepng_palette_clear(mode_out);
          for(i = 0; i < profile.numcolors; i++)
          {
            error = lodepng_palette_add(mode_out, p[i * 4 + 0], p[i * 4 + 1], p[i * 4 + 2], p[i * 4 + 3]);
            if(error) break;
          }

          mode_out->colortype = LCT_PALETTE;
          mode_out->bitdepth = palettebits;
        }
      }
      else /*8-bit per channel*/
      {
        mode_out->bitdepth = 8;
        if(profile.alpha)
        {
          mode_out->colortype = profile.colored ? LCT_RGBA : LCT_GREY_ALPHA;
        }
        else
        {
          mode_out->colortype = profile.colored ? LCT_RGB : LCT_GREY /*LCT_GREY normally won't occur, already done earlier*/;
          if(profile.key) setColorKeyFrom16bit(mode_out, profile.key_r, profile.key_g, profile.key_b, mode_out->bitdepth);
        }
      }
    }
  }

  color_profile_cleanup(&profile);

  if(mode_out->colortype == LCT_PALETTE && mode_in->palettesize == mode_out->palettesize)
  {
    /*In this case keep the palette order of the input, so that the user can choose an optimal one*/
    size_t i;
    for(i = 0; i < mode_in->palettesize * 4; i++)
    {
      mode_out->palette[i] = mode_in->palette[i];
    }
  }

  if(no_nibbles && mode_out->bitdepth < 8)
  {
    /*palette can keep its small amount of colors, as long as no indices use it*/
    mode_out->bitdepth = 8;
  }

  return error;
}