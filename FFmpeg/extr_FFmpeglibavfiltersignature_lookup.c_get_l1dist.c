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
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {scalar_t__* l1distlut; } ;
typedef  TYPE_1__ SignatureContext ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int SIGELEM_SIZE ; 

__attribute__((used)) static unsigned int get_l1dist(AVFilterContext *ctx, SignatureContext *sc, const uint8_t *first, const uint8_t *second)
{
    unsigned int i;
    unsigned int dist = 0;
    uint8_t f, s;

    for (i = 0; i < SIGELEM_SIZE/5; i++) {
        if (first[i] != second[i]) {
            f = first[i];
            s = second[i];
            if (f > s) {
                /* little variation of gauss sum formula */
                dist += sc->l1distlut[243*242/2 - (243-s)*(242-s)/2 + f - s - 1];
            } else {
                dist += sc->l1distlut[243*242/2 - (243-f)*(242-f)/2 + s - f - 1];
            }
        }
    }
    return dist;
}