#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_14__ ;
typedef  struct TYPE_23__   TYPE_13__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct TYPE_25__ {int /*<<< orphan*/  memory; } ;
struct TYPE_33__ {TYPE_1__ root; } ;
struct TYPE_32__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_31__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_30__ {TYPE_5__* internal; } ;
struct TYPE_29__ {scalar_t__ glyph_hints; TYPE_10__* loader; } ;
struct TYPE_28__ {int /*<<< orphan*/  internal; } ;
struct TYPE_27__ {int /*<<< orphan*/  outline; } ;
struct TYPE_26__ {int /*<<< orphan*/  outline; } ;
struct TYPE_24__ {int load_points; TYPE_8__ advance; TYPE_7__ left_bearing; scalar_t__ pos_y; scalar_t__ pos_x; scalar_t__ hints_funcs; void* hints_globals; int /*<<< orphan*/ * current; int /*<<< orphan*/ * base; TYPE_10__* loader; int /*<<< orphan*/  memory; TYPE_13__* glyph; TYPE_9__* face; scalar_t__ path_begun; } ;
struct TYPE_23__ {TYPE_6__ root; } ;
struct TYPE_22__ {scalar_t__ topfont; } ;
struct TYPE_21__ {TYPE_4__ root; } ;
struct TYPE_20__ {TYPE_3__ current; TYPE_2__ base; } ;
typedef  TYPE_9__* TT_Face ;
typedef  TYPE_10__* FT_GlyphLoader ;
typedef  scalar_t__ FT_Bool ;
typedef  TYPE_11__* CFF_Size ;
typedef  TYPE_12__* CFF_Internal ;
typedef  TYPE_13__* CFF_GlyphSlot ;
typedef  TYPE_14__ CFF_Builder ;

/* Variables and functions */
 int /*<<< orphan*/  FT_GlyphLoader_Rewind (TYPE_10__*) ; 

__attribute__((used)) static void
  cff_builder_init( CFF_Builder*   builder,
                    TT_Face        face,
                    CFF_Size       size,
                    CFF_GlyphSlot  glyph,
                    FT_Bool        hinting )
  {
    builder->path_begun  = 0;
    builder->load_points = 1;

    builder->face   = face;
    builder->glyph  = glyph;
    builder->memory = face->root.memory;

    if ( glyph )
    {
      FT_GlyphLoader  loader = glyph->root.internal->loader;


      builder->loader  = loader;
      builder->base    = &loader->base.outline;
      builder->current = &loader->current.outline;
      FT_GlyphLoader_Rewind( loader );

      builder->hints_globals = 0;
      builder->hints_funcs   = 0;

      if ( hinting && size )
      {
        CFF_Internal  internal = (CFF_Internal)size->root.internal;


        builder->hints_globals = (void *)internal->topfont;
        builder->hints_funcs   = glyph->root.internal->glyph_hints;
      }
    }

    builder->pos_x = 0;
    builder->pos_y = 0;

    builder->left_bearing.x = 0;
    builder->left_bearing.y = 0;
    builder->advance.x      = 0;
    builder->advance.y      = 0;
  }