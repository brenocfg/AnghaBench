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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int EDGE_BOTTOM ; 
 int EDGE_TOP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void draw_edges_8_c(uint8_t *buf, int wrap, int width, int height,
                           int w, int h, int sides)
{
    uint8_t *ptr = buf, *last_line;
    int i;

    /* left and right */
    for (i = 0; i < height; i++) {
        memset(ptr - w, ptr[0], w);
        memset(ptr + width, ptr[width - 1], w);
        ptr += wrap;
    }

    /* top and bottom + corners */
    buf -= w;
    last_line = buf + (height - 1) * wrap;
    if (sides & EDGE_TOP)
        for (i = 0; i < h; i++)
            // top
            memcpy(buf - (i + 1) * wrap, buf, width + w + w);
    if (sides & EDGE_BOTTOM)
        for (i = 0; i < h; i++)
            // bottom
            memcpy(last_line + (i + 1) * wrap, last_line, width + w + w);
}