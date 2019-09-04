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
typedef  scalar_t__ int16_t ;
struct TYPE_3__ {int* newvec; scalar_t__* filtbuf; } ;
typedef  TYPE_1__ TSContext ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,int) ; 

__attribute__((used)) static void truespeech_update_filters(TSContext *dec, int16_t *out, int quart)
{
    int i;

    memmove(dec->filtbuf, &dec->filtbuf[60], 86 * sizeof(*dec->filtbuf));
    for(i = 0; i < 60; i++){
        dec->filtbuf[i + 86] = out[i] + dec->newvec[i] - (dec->newvec[i] >> 3);
        out[i] += dec->newvec[i];
    }
}