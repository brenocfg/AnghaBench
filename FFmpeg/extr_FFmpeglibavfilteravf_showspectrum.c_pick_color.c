#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {float a; float y; float u; float v; } ;
struct TYPE_5__ {int color_mode; } ;
typedef  TYPE_1__ ShowSpectrumContext ;

/* Variables and functions */
 int CHANNEL ; 
 int FF_ARRAY_ELEMS (TYPE_3__*) ; 
 TYPE_3__** color_table ; 

__attribute__((used)) static void pick_color(ShowSpectrumContext *s,
                       float yf, float uf, float vf,
                       float a, float *out)
{
    if (s->color_mode > CHANNEL) {
        const int cm = s->color_mode;
        float y, u, v;
        int i;

        for (i = 1; i < FF_ARRAY_ELEMS(color_table[cm]) - 1; i++)
            if (color_table[cm][i].a >= a)
                break;
        // i now is the first item >= the color
        // now we know to interpolate between item i - 1 and i
        if (a <= color_table[cm][i - 1].a) {
            y = color_table[cm][i - 1].y;
            u = color_table[cm][i - 1].u;
            v = color_table[cm][i - 1].v;
        } else if (a >= color_table[cm][i].a) {
            y = color_table[cm][i].y;
            u = color_table[cm][i].u;
            v = color_table[cm][i].v;
        } else {
            float start = color_table[cm][i - 1].a;
            float end = color_table[cm][i].a;
            float lerpfrac = (a - start) / (end - start);
            y = color_table[cm][i - 1].y * (1.0f - lerpfrac)
              + color_table[cm][i].y * lerpfrac;
            u = color_table[cm][i - 1].u * (1.0f - lerpfrac)
              + color_table[cm][i].u * lerpfrac;
            v = color_table[cm][i - 1].v * (1.0f - lerpfrac)
              + color_table[cm][i].v * lerpfrac;
        }

        out[0] = y * yf;
        out[1] = u * uf;
        out[2] = v * vf;
    } else {
        out[0] = a * yf;
        out[1] = a * uf;
        out[2] = a * vf;
    }
}