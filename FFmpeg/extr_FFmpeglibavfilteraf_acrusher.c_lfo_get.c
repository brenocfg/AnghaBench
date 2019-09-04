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
struct TYPE_3__ {double phase; double amount; scalar_t__ offset; int /*<<< orphan*/  pwidth; } ;
typedef  TYPE_1__ LFOContext ;

/* Variables and functions */
 scalar_t__ FFMAX (double,int /*<<< orphan*/ ) ; 
 double FFMIN (int,scalar_t__) ; 
 double M_PI ; 
 double fmod (double,int) ; 
 double sin (double) ; 

__attribute__((used)) static double lfo_get(LFOContext *lfo)
{
    double phs = FFMIN(100., lfo->phase / FFMIN(1.99, FFMAX(0.01, lfo->pwidth)) + lfo->offset);
    double val;

    if (phs > 1)
        phs = fmod(phs, 1.);

    val = sin((phs * 360.) * M_PI / 180);

    return val * lfo->amount;
}