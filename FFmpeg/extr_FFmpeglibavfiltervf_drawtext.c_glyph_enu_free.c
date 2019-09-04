#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  border_glyph; int /*<<< orphan*/  glyph; } ;
typedef  TYPE_1__ Glyph ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Done_Glyph (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (void*) ; 

__attribute__((used)) static int glyph_enu_free(void *opaque, void *elem)
{
    Glyph *glyph = elem;

    FT_Done_Glyph(glyph->glyph);
    FT_Done_Glyph(glyph->border_glyph);
    av_free(elem);
    return 0;
}