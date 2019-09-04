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
struct TYPE_6__ {int buffer; int pitch; int width; int rows; } ;
struct TYPE_5__ {int line; int pitch; int width; int rows; int total; } ;
typedef  TYPE_1__* PFR_BitWriter ;
typedef  int /*<<< orphan*/  FT_Bool ;
typedef  TYPE_2__ FT_Bitmap ;

/* Variables and functions */

__attribute__((used)) static void
  pfr_bitwriter_init( PFR_BitWriter  writer,
                      FT_Bitmap*     target,
                      FT_Bool        decreasing )
  {
    writer->line   = target->buffer;
    writer->pitch  = target->pitch;
    writer->width  = target->width;
    writer->rows   = target->rows;
    writer->total  = writer->width * writer->rows;

    if ( !decreasing )
    {
      writer->line += writer->pitch * ( target->rows-1 );
      writer->pitch = -writer->pitch;
    }
  }