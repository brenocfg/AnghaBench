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
struct TYPE_3__ {int saturation; int /*<<< orphan*/  hue; void* hue_cos; void* hue_sin; } ;
typedef  TYPE_1__ HueContext ;

/* Variables and functions */
 int cos (int /*<<< orphan*/ ) ; 
 void* lrint (int) ; 
 int sin (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void compute_sin_and_cos(HueContext *hue)
{
    /*
     * Scale the value to the norm of the resulting (U,V) vector, that is
     * the saturation.
     * This will be useful in the apply_lut function.
     */
    hue->hue_sin = lrint(sin(hue->hue) * (1 << 16) * hue->saturation);
    hue->hue_cos = lrint(cos(hue->hue) * (1 << 16) * hue->saturation);
}