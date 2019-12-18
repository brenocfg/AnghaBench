#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  guint8 ;
typedef  scalar_t__ gint ;
typedef  int /*<<< orphan*/  GdkPixbuf ;

/* Variables and functions */
 int /*<<< orphan*/  horz_line (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vert_line (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
hash_pixbuf(
    GdkPixbuf * pb,
    gint        x,
    gint        y,
    gint        w,
    gint        h,
    gint        step,
    gint        orientation)
{
    gint ii, jj;
    gint line_width = 8;
    struct
    {
        guint8 r;
        guint8 g;
        guint8 b;
    } c[4] =
    {{0x80, 0x80, 0x80},{0xC0, 0x80, 0x70},{0x80, 0xA0, 0x80},{0x70, 0x80, 0xA0}};

    if (!orientation)
    {
        // vertical lines
        for (ii = x, jj = 0; ii+line_width < x+w; ii += step, jj++)
        {
            vert_line(pb, c[jj&3].r, c[jj&3].g, c[jj&3].b, ii, y, h, line_width);
        }
    }
    else
    {
        // horizontal lines
        for (ii = y, jj = 0; ii+line_width < y+h; ii += step, jj++)
        {
            horz_line(pb, c[jj&3].r, c[jj&3].g, c[jj&3].b, x, ii, w, line_width);
        }
    }
}