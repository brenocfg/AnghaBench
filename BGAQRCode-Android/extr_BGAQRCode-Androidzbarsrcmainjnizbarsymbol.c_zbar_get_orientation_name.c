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
typedef  int zbar_orientation_t ;

/* Variables and functions */
#define  ZBAR_ORIENT_DOWN 131 
#define  ZBAR_ORIENT_LEFT 130 
#define  ZBAR_ORIENT_RIGHT 129 
#define  ZBAR_ORIENT_UP 128 

const char *zbar_get_orientation_name (zbar_orientation_t orient)
{
    switch(orient) {
    case ZBAR_ORIENT_UP: return("UP");
    case ZBAR_ORIENT_RIGHT: return("RIGHT");
    case ZBAR_ORIENT_DOWN: return("DOWN");
    case ZBAR_ORIENT_LEFT: return("LEFT");
    default: return("UNKNOWN");
    }
}