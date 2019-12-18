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
struct TYPE_3__ {int pscrn; int fapprox; int /*<<< orphan*/  expfunc; int /*<<< orphan*/  dot_prod; int /*<<< orphan*/  extract; int /*<<< orphan*/  wae5; int /*<<< orphan*/  compute_network0; int /*<<< orphan*/  readpixels; int /*<<< orphan*/  process_line0; int /*<<< orphan*/  evalfunc_1; int /*<<< orphan*/  evalfunc_0; int /*<<< orphan*/  copy_pad; } ;
typedef  TYPE_1__ NNEDIContext ;

/* Variables and functions */
 int /*<<< orphan*/  byte2word48 ; 
 int /*<<< orphan*/  byte2word64 ; 
 int /*<<< orphan*/  compute_network0 ; 
 int /*<<< orphan*/  compute_network0_i16 ; 
 int /*<<< orphan*/  compute_network0new ; 
 int /*<<< orphan*/  copy_pad ; 
 int /*<<< orphan*/  dot_prod ; 
 int /*<<< orphan*/  dot_prods ; 
 int /*<<< orphan*/  e2_m16 ; 
 int /*<<< orphan*/  evalfunc_0 ; 
 int /*<<< orphan*/  evalfunc_1 ; 
 int /*<<< orphan*/  extract_m8 ; 
 int /*<<< orphan*/  extract_m8_i16 ; 
 int /*<<< orphan*/  pixel2float48 ; 
 int /*<<< orphan*/  process_line0 ; 
 int /*<<< orphan*/  weighted_avg_elliott_mul5_m16 ; 

__attribute__((used)) static void select_functions(NNEDIContext *s)
{
    s->copy_pad = copy_pad;
    s->evalfunc_0 = evalfunc_0;
    s->evalfunc_1 = evalfunc_1;

    // evalfunc_0
    s->process_line0 = process_line0;

    if (s->pscrn < 2) { // original prescreener
        if (s->fapprox & 1) { // int16 dot products
            s->readpixels = byte2word48;
            s->compute_network0 = compute_network0_i16;
        } else {
            s->readpixels = pixel2float48;
            s->compute_network0 = compute_network0;
        }
    } else { // new prescreener
        // only int16 dot products
        s->readpixels = byte2word64;
        s->compute_network0 = compute_network0new;
    }

    // evalfunc_1
    s->wae5 = weighted_avg_elliott_mul5_m16;

    if (s->fapprox & 2) { // use int16 dot products
        s->extract = extract_m8_i16;
        s->dot_prod = dot_prods;
    } else { // use float dot products
        s->extract = extract_m8;
        s->dot_prod = dot_prod;
    }

    s->expfunc = e2_m16;
}