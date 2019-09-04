#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int dx; int dy; scalar_t__ dh; scalar_t__ dw; } ;
typedef  TYPE_1__ dbox ;
struct TYPE_7__ {int x; int w; int y; int h; } ;
typedef  TYPE_2__ box ;

/* Variables and functions */

dbox derivative(box a, box b)
{
    dbox d;
    d.dx = 0;
    d.dw = 0;
    float l1 = a.x - a.w/2;
    float l2 = b.x - b.w/2;
    if (l1 > l2){
        d.dx -= 1;
        d.dw += .5;
    }
    float r1 = a.x + a.w/2;
    float r2 = b.x + b.w/2;
    if(r1 < r2){
        d.dx += 1;
        d.dw += .5;
    }
    if (l1 > r2) {
        d.dx = -1;
        d.dw = 0;
    }
    if (r1 < l2){
        d.dx = 1;
        d.dw = 0;
    }

    d.dy = 0;
    d.dh = 0;
    float t1 = a.y - a.h/2;
    float t2 = b.y - b.h/2;
    if (t1 > t2){
        d.dy -= 1;
        d.dh += .5;
    }
    float b1 = a.y + a.h/2;
    float b2 = b.y + b.h/2;
    if(b1 < b2){
        d.dy += 1;
        d.dh += .5;
    }
    if (t1 > b2) {
        d.dy = -1;
        d.dh = 0;
    }
    if (b1 < t2){
        d.dy = 1;
        d.dh = 0;
    }
    return d;
}