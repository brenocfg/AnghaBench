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
struct TYPE_5__ {TYPE_1__* face; } ;
struct TYPE_4__ {scalar_t__ num_glyphs; } ;
typedef  TYPE_2__* GXV_Validator ;
typedef  scalar_t__ FT_UShort ;
typedef  int /*<<< orphan*/  FT_String ;

/* Variables and functions */
 int /*<<< orphan*/  FT_INVALID_GLYPH_ID ; 
 int /*<<< orphan*/  GXV_SET_ERR_IF_PARANOID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GXV_TRACE (char*) ; 

__attribute__((used)) static void
  gxv_just_check_max_gid( FT_UShort         gid,
                          const FT_String*  msg_tag,
                          GXV_Validator     gxvalid )
  {
    if ( gid < gxvalid->face->num_glyphs )
      return;

    GXV_TRACE(( "just table includes too large %s"
                " GID=%d > %d (in maxp)\n",
                msg_tag, gid, gxvalid->face->num_glyphs ));
    GXV_SET_ERR_IF_PARANOID( FT_INVALID_GLYPH_ID );
  }