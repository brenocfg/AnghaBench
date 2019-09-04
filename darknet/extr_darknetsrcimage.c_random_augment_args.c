#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {float h; float w; } ;
typedef  TYPE_1__ image ;
struct TYPE_6__ {float rad; float scale; int w; int h; float dx; float dy; float aspect; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ augment_args ;

/* Variables and functions */
 int TWO_PI ; 
 int rand_int (int,int) ; 
 float rand_scale (float) ; 
 int rand_uniform (float,float) ; 

augment_args random_augment_args(image im, float angle, float aspect, int low, int high, int w, int h)
{
    augment_args a = {0};
    aspect = rand_scale(aspect);
    int r = rand_int(low, high);
    int min = (im.h < im.w*aspect) ? im.h : im.w*aspect;
    float scale = (float)r / min;

    float rad = rand_uniform(-angle, angle) * TWO_PI / 360.;

    float dx = (im.w*scale/aspect - w) / 2.;
    float dy = (im.h*scale - w) / 2.;
    //if(dx < 0) dx = 0;
    //if(dy < 0) dy = 0;
    dx = rand_uniform(-dx, dx);
    dy = rand_uniform(-dy, dy);

    a.rad = rad;
    a.scale = scale;
    a.w = w;
    a.h = h;
    a.dx = dx;
    a.dy = dy;
    a.aspect = aspect;
    return a;
}