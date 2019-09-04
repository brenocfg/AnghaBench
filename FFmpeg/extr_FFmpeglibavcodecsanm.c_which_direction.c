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
typedef  enum GlyphDir { ____Placeholder_GlyphDir } GlyphDir ;

/* Variables and functions */
 int BOTTOM_EDGE ; 
 int DIR_DOWN ; 
 int DIR_LEFT ; 
 int DIR_RIGHT ; 
 int DIR_UP ; 
 int LEFT_EDGE ; 
 int NO_DIR ; 
 int RIGHT_EDGE ; 
 int TOP_EDGE ; 

__attribute__((used)) static enum GlyphDir which_direction(enum GlyphEdge edge0, enum GlyphEdge edge1)
{
    if ((edge0 == LEFT_EDGE && edge1 == RIGHT_EDGE) ||
        (edge1 == LEFT_EDGE && edge0 == RIGHT_EDGE) ||
        (edge0 == BOTTOM_EDGE && edge1 != TOP_EDGE) ||
        (edge1 == BOTTOM_EDGE && edge0 != TOP_EDGE))
        return DIR_UP;
    else if ((edge0 == TOP_EDGE && edge1 != BOTTOM_EDGE) ||
             (edge1 == TOP_EDGE && edge0 != BOTTOM_EDGE))
        return DIR_DOWN;
    else if ((edge0 == LEFT_EDGE && edge1 != RIGHT_EDGE) ||
             (edge1 == LEFT_EDGE && edge0 != RIGHT_EDGE))
        return DIR_LEFT;
    else if ((edge0 == TOP_EDGE && edge1 == BOTTOM_EDGE) ||
             (edge1 == TOP_EDGE && edge0 == BOTTOM_EDGE) ||
             (edge0 == RIGHT_EDGE && edge1 != LEFT_EDGE) ||
             (edge1 == RIGHT_EDGE && edge0 != LEFT_EDGE))
        return DIR_RIGHT;

    return NO_DIR;
}