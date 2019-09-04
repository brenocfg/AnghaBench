#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ num_fixed_sizes; int /*<<< orphan*/  available_sizes; } ;
struct TYPE_7__ {TYPE_1__ root; } ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  TYPE_2__* FNT_Face ;

/* Variables and functions */
 int /*<<< orphan*/  FT_FACE_MEMORY (TYPE_2__*) ; 
 int /*<<< orphan*/  FT_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnt_font_done (TYPE_2__*) ; 

__attribute__((used)) static void
  FNT_Face_Done( FNT_Face  face )
  {
    FT_Memory  memory;


    if ( !face )
      return;

    memory = FT_FACE_MEMORY( face );

    fnt_font_done( face );

    FT_FREE( face->root.available_sizes );
    face->root.num_fixed_sizes = 0;
  }