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
typedef  enum GlyphEdge { ____Placeholder_GlyphEdge } GlyphEdge ;

/* Variables and functions */
 int BOTTOM_EDGE ; 
 int LEFT_EDGE ; 
 int NO_EDGE ; 
 int RIGHT_EDGE ; 
 int TOP_EDGE ; 

__attribute__((used)) static enum GlyphEdge which_edge(int x, int y, int edge_size)
{
    const int edge_max = edge_size - 1;

    if (!y)
        return BOTTOM_EDGE;
    else if (y == edge_max)
        return TOP_EDGE;
    else if (!x)
        return LEFT_EDGE;
    else if (x == edge_max)
        return RIGHT_EDGE;
    else
        return NO_EDGE;
}