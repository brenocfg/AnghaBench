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
struct TYPE_5__ {int metrics_loaded; TYPE_1__* metrics; } ;
struct TYPE_4__ {void* vertAdvance; void* vertBearingY; void* vertBearingX; void* horiAdvance; void* horiBearingY; void* horiBearingX; void* width; void* height; } ;
typedef  TYPE_1__* TT_SBit_Metrics ;
typedef  TYPE_2__* TT_SBitDecoder ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  void* FT_Char ;
typedef  void* FT_Byte ;
typedef  scalar_t__ FT_Bool ;

/* Variables and functions */
 int /*<<< orphan*/  SFNT_Err_Invalid_Argument ; 
 int /*<<< orphan*/  SFNT_Err_Ok ; 

__attribute__((used)) static FT_Error
  tt_sbit_decoder_load_metrics( TT_SBitDecoder  decoder,
                                FT_Byte*       *pp,
                                FT_Byte*        limit,
                                FT_Bool         big )
  {
    FT_Byte*         p       = *pp;
    TT_SBit_Metrics  metrics = decoder->metrics;


    if ( p + 5 > limit )
      goto Fail;

    metrics->height       = p[0];
    metrics->width        = p[1];
    metrics->horiBearingX = (FT_Char)p[2];
    metrics->horiBearingY = (FT_Char)p[3];
    metrics->horiAdvance  = p[4];

    p += 5;
    if ( big )
    {
      if ( p + 3 > limit )
        goto Fail;

      metrics->vertBearingX = (FT_Char)p[0];
      metrics->vertBearingY = (FT_Char)p[1];
      metrics->vertAdvance  = p[2];

      p += 3;
    }

    decoder->metrics_loaded = 1;
    *pp = p;
    return SFNT_Err_Ok;

  Fail:
    return SFNT_Err_Invalid_Argument;
  }