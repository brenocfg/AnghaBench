#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * color_map; } ;
typedef  TYPE_1__ vbi_page ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int VBI_B (int /*<<< orphan*/ ) ; 
 int VBI_G (int /*<<< orphan*/ ) ; 
 int VBI_R (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_bprintf (int /*<<< orphan*/ *,char*,char const*,int,int,int) ; 

__attribute__((used)) static void bprint_color(const char *type, AVBPrint *buf, vbi_page *page, unsigned ci)
{
    int r = VBI_R(page->color_map[ci]);
    int g = VBI_G(page->color_map[ci]);
    int b = VBI_B(page->color_map[ci]);
    av_bprintf(buf, "{\\%s&H%02X%02X%02X&}", type, b, g, r);
}