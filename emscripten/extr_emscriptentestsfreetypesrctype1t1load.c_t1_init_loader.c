#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ init; } ;
struct TYPE_12__ {scalar_t__ init; } ;
struct TYPE_11__ {scalar_t__ init; } ;
struct TYPE_10__ {scalar_t__ init; } ;
struct TYPE_9__ {scalar_t__ init; } ;
struct TYPE_14__ {scalar_t__ keywords_encountered; scalar_t__ fontdata; TYPE_5__ swap_table; TYPE_4__ subrs; TYPE_3__ glyph_names; TYPE_2__ charstrings; TYPE_1__ encoding_table; scalar_t__ num_chars; scalar_t__ num_glyphs; } ;
typedef  TYPE_6__* T1_Loader ;
typedef  int /*<<< orphan*/  T1_Face ;

/* Variables and functions */
 int /*<<< orphan*/  FT_MEM_ZERO (TYPE_6__*,int) ; 
 int /*<<< orphan*/  FT_UNUSED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  t1_init_loader( T1_Loader  loader,
                  T1_Face    face )
  {
    FT_UNUSED( face );

    FT_MEM_ZERO( loader, sizeof ( *loader ) );
    loader->num_glyphs = 0;
    loader->num_chars  = 0;

    /* initialize the tables -- simply set their `init' field to 0 */
    loader->encoding_table.init  = 0;
    loader->charstrings.init     = 0;
    loader->glyph_names.init     = 0;
    loader->subrs.init           = 0;
    loader->swap_table.init      = 0;
    loader->fontdata             = 0;
    loader->keywords_encountered = 0;
  }