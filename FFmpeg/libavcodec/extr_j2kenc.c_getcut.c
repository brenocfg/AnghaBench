#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_5__ {int npasses; TYPE_1__* passes; } ;
struct TYPE_4__ {int rate; int disto; } ;
typedef  TYPE_2__ Jpeg2000Cblk ;

/* Variables and functions */
 int WMSEDEC_SHIFT ; 

__attribute__((used)) static int getcut(Jpeg2000Cblk *cblk, int64_t lambda, int dwt_norm)
{
    int passno, res = 0;
    for (passno = 0; passno < cblk->npasses; passno++){
        int dr;
        int64_t dd;

        dr = cblk->passes[passno].rate
           - (res ? cblk->passes[res-1].rate:0);
        dd = cblk->passes[passno].disto
           - (res ? cblk->passes[res-1].disto:0);

        if (((dd * dwt_norm) >> WMSEDEC_SHIFT) * dwt_norm >= dr * lambda)
            res = passno+1;
    }
    return res;
}