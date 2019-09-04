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
typedef  float GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 

void ortho(float  left,  float  right,  float  bottom,  float  top,  float  nearVal,  float  farVal, GLfloat *projMatrix) {
    float tx = -(right+left)/(right-left);
    float ty = -(top+bottom)/(top-bottom);
    float tz = -(farVal+nearVal)/(farVal-nearVal);
    memset(projMatrix, 0, 16 * sizeof(GLfloat));
    projMatrix[0] = 2.0f / (right-left);
    projMatrix[3] = tx;
    projMatrix[1*4+1] = 2.0f / (top-bottom);
    projMatrix[1*4+3] = ty;
    projMatrix[2*4+2] = -2.0f / (farVal-nearVal);
    projMatrix[2*4+3] = tz;
    projMatrix[3*4+3] = 1.0f;
}