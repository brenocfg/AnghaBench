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
typedef  int int32_t ;

/* Variables and functions */
 int CONV_DB (double) ; 
 double M_PI ; 
 double cos (double) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 double sin (double) ; 

void av_display_rotation_set(int32_t matrix[9], double angle)
{
    double radians = -angle * M_PI / 180.0f;
    double c = cos(radians);
    double s = sin(radians);

    memset(matrix, 0, 9 * sizeof(int32_t));

    matrix[0] = CONV_DB(c);
    matrix[1] = CONV_DB(-s);
    matrix[3] = CONV_DB(s);
    matrix[4] = CONV_DB(c);
    matrix[8] = 1 << 30;
}