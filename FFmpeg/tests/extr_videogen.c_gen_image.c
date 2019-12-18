#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int x; int y; int w; int h; int r; int g; int b; } ;
typedef  TYPE_1__ VObj ;

/* Variables and functions */
 int FRAC_BITS ; 
 int FRAC_ONE ; 
 int NB_OBJS ; 
 int NOISE_W ; 
 int NOISE_X ; 
 int NOISE_Y ; 
 int int_cos (int) ; 
 int myrnd (unsigned int*,int) ; 
 TYPE_1__* objs ; 
 int /*<<< orphan*/  put_pixel (int,int,int,int,int) ; 
 unsigned int seed ; 

__attribute__((used)) static void gen_image(int num, int w, int h)
{
    int r, g, b, x, y, i, dx, dy, x1, y1;
    unsigned int seed1;

    if (num == 0) {
        for (i = 0; i < NB_OBJS; i++) {
            objs[i].x = myrnd(&seed, w);
            objs[i].y = myrnd(&seed, h);
            objs[i].w = myrnd(&seed, w / 4) + 10;
            objs[i].h = myrnd(&seed, h / 4) + 10;
            objs[i].r = myrnd(&seed, 256);
            objs[i].g = myrnd(&seed, 256);
            objs[i].b = myrnd(&seed, 256);
        }
    }

    /* first a moving background with gradients */
    /* test motion estimation */
    dx = int_cos(num * FRAC_ONE / 50) * 35;
    dy = int_cos(num * FRAC_ONE / 50 + FRAC_ONE / 10) * 30;
    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            x1 = (x << FRAC_BITS) + dx;
            y1 = (y << FRAC_BITS) + dy;
            r  =       ((y1  * 7) >> FRAC_BITS) & 0xff;
            g  = (((x1 + y1) * 9) >> FRAC_BITS) & 0xff;
            b  =  ((x1       * 5) >> FRAC_BITS) & 0xff;
            put_pixel(x, y, r, g, b);
        }
    }

    /* then some noise with very high intensity to test saturation */
    seed1 = num;
    for (y = 0; y < NOISE_W; y++) {
        for (x = 0; x < NOISE_W; x++) {
            r = myrnd(&seed1, 256);
            g = myrnd(&seed1, 256);
            b = myrnd(&seed1, 256);
            put_pixel(x + NOISE_X, y + NOISE_Y, r, g, b);
        }
    }

    /* then moving objects */
    for (i = 0; i < NB_OBJS; i++) {
        VObj *p = &objs[i];
        seed1 = i;
        for (y = 0; y < p->h; y++) {
            for (x = 0; x < p->w; x++) {
                r = p->r;
                g = p->g;
                b = p->b;
                /* add a per object noise */
                r += myrnd(&seed1, 50);
                g += myrnd(&seed1, 50);
                b += myrnd(&seed1, 50);
                put_pixel(x + p->x, y + p->y, r, g, b);
            }
        }
        p->x += myrnd(&seed, 21) - 10;
        p->y += myrnd(&seed, 21) - 10;
    }
}