#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int h; int y; int w; int x; } ;
struct TYPE_6__ {TYPE_1__ viewport; } ;
struct TYPE_5__ {int aspect; int overscan; scalar_t__ yscale; scalar_t__ xscale; scalar_t__ render; int /*<<< orphan*/  gg_extra; } ;

/* Variables and functions */
 scalar_t__ MCLOCK_NTSC ; 
 scalar_t__ SYSTEM_GG ; 
 int VI_MAX_HEIGHT_NTSC ; 
 int VI_MAX_HEIGHT_PAL ; 
 TYPE_3__ bitmap ; 
 TYPE_2__ config ; 
 scalar_t__ gc_pal ; 
 int* reg ; 
 scalar_t__ system_clock ; 
 scalar_t__ system_hw ; 
 scalar_t__ vdp_pal ; 

__attribute__((used)) static void gxSetAspectRatio(int *xscale, int *yscale)
{
  /* Vertical Scaling is disabled by default */
  *yscale = (bitmap.viewport.h + (2 * bitmap.viewport.y)) / 2;

  /* Original aspect ratio */
  if (config.aspect)
  {
    /* Adjust vertical scaling when input & output video heights are different */
    if (vdp_pal && (!gc_pal || config.render))
    {
      *yscale = *yscale * VI_MAX_HEIGHT_NTSC / VI_MAX_HEIGHT_PAL;
    }
    else if (!vdp_pal && gc_pal && !config.render)
    {
      *yscale = *yscale * VI_MAX_HEIGHT_PAL / VI_MAX_HEIGHT_NTSC;
    }

    /* Horizontal Scaling */
    /* Wii/Gamecube pixel clock = 13.5 Mhz */
    /* "H32" pixel clock = Master Clock / 10 = 5.3693175 Mhz (NTSC) or 5.3203424 (PAL) */
    /* "H40" pixel clock = Master Clock / 8 = 6,711646875 Mhz (NTSC) or 6,650428 Mhz (PAL) */
    if (config.overscan & 2)
    {
      /* Horizontal borders are emulated */
      if (reg[12] & 1)
      {
        /* 348 "H40" pixels = 348 * Wii/GC pixel clock / "H40" pixel clock = approx. 700 (NTSC) or 707 (PAL) Wii/GC pixels */
        *xscale = (system_clock == MCLOCK_NTSC) ? 350 : 354; 
      }
      else
      {
        /* 284 "H32" pixels = 284 * Wii/GC pixel clock / "H40" pixel clock = approx. 714 (NTSC) or 721 (PAL) Wii/GC pixels */
        *xscale = (system_clock == MCLOCK_NTSC) ? 357 : 361; 
      }
    }
    else
    {
      /* Horizontal borders are simulated */
      if ((system_hw == SYSTEM_GG) && !config.gg_extra)
      {
        /* 160 "H32" pixels = 160 * Wii/GC pixel clock / "H32" pixel clock = approx. 403 Wii/GC pixels (NTSC only) */
        *xscale = 202;
      }
      else
      {
        /* 320 "H40" pixels = 256 "H32" pixels = 256 * Wii/GC pixel clock / "H32" pixel clock = approx. 644 (NTSC) or 650 (PAL) Wii/GC pixels */
        *xscale = (system_clock == MCLOCK_NTSC) ? 322 : 325; 
      }
    }

    /* Aspect correction for widescreen TV */
    if (config.aspect & 2)
    {
      /* Keep 4:3 aspect ratio on 16:9 output */
      *xscale = (*xscale * 3) / 4;
    }
  }

  /* Manual aspect ratio */
  else
  {
    /* By default, disable horizontal scaling */
    *xscale = bitmap.viewport.w + (2 * bitmap.viewport.x);
      
    /* Keep original aspect ratio in H32 modes */
    if (!(reg[12] & 1))
    {
        *xscale = (*xscale * 320) / 256;
    }

    /* Game Gear specific: if borders are disabled, upscale to fullscreen */
    if ((system_hw == SYSTEM_GG) && !config.gg_extra)
    {
      if (!(config.overscan & 1))
      {
        /* Active area height = approx. 224 non-interlaced lines (60hz) */
        *yscale = 112;
      }

      if (!(config.overscan & 2))
      {
        /* Active area width = approx. 640 pixels */
        *xscale = 320;
      }
    }

    /* By default, keep NTSC aspect ratio */
    if (gc_pal && !config.render)
    {
      /* Upscale PAL output */
      *yscale = *yscale * VI_MAX_HEIGHT_PAL / VI_MAX_HEIGHT_NTSC;
    }

    /* Add user scaling */
    *xscale += config.xscale;
    *yscale += config.yscale;
  }
}