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
struct SwrContext {scalar_t__ resample; scalar_t__ delayed_samples_fixup; } ;
typedef  int /*<<< orphan*/  soxr_t ;

/* Variables and functions */
 scalar_t__ soxr_delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soxr_process (int /*<<< orphan*/ ,float*,int /*<<< orphan*/ ,size_t*,float*,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int flush(struct SwrContext *s){
    s->delayed_samples_fixup = soxr_delay((soxr_t)s->resample);

    soxr_process((soxr_t)s->resample, NULL, 0, NULL, NULL, 0, NULL);

    {
        float f;
        size_t idone, odone;
        soxr_process((soxr_t)s->resample, &f, 0, &idone, &f, 0, &odone);
        s->delayed_samples_fixup -= soxr_delay((soxr_t)s->resample);
    }

    return 0;
}