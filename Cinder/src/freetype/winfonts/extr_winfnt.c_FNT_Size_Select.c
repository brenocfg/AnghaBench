#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* font; } ;
struct TYPE_7__ {int ascender; int descender; int max_advance; } ;
struct TYPE_10__ {TYPE_1__ metrics; int /*<<< orphan*/  face; } ;
struct TYPE_9__ {int ascent; int pixel_height; int max_width; } ;
struct TYPE_8__ {TYPE_3__ header; } ;
typedef  TYPE_3__* FT_WinFNT_Header ;
typedef  int /*<<< orphan*/  FT_ULong ;
typedef  TYPE_4__* FT_Size ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  TYPE_5__* FNT_Face ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Err_Ok ; 
 int /*<<< orphan*/  FT_Select_Metrics (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_UNUSED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static FT_Error
  FNT_Size_Select( FT_Size   size,
                   FT_ULong  strike_index )
  {
    FNT_Face          face   = (FNT_Face)size->face;
    FT_WinFNT_Header  header = &face->font->header;

    FT_UNUSED( strike_index );


    FT_Select_Metrics( size->face, 0 );

    size->metrics.ascender    = header->ascent * 64;
    size->metrics.descender   = -( header->pixel_height -
                                   header->ascent ) * 64;
    size->metrics.max_advance = header->max_width * 64;

    return FT_Err_Ok;
  }