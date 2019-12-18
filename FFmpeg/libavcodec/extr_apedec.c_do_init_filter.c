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
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_3__ {scalar_t__ avg; int /*<<< orphan*/ * coeffs; int /*<<< orphan*/ * historybuffer; int /*<<< orphan*/ * adaptcoeffs; int /*<<< orphan*/ * delay; } ;
typedef  TYPE_1__ APEFilter ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void do_init_filter(APEFilter *f, int16_t *buf, int order)
{
    f->coeffs = buf;
    f->historybuffer = buf + order;
    f->delay       = f->historybuffer + order * 2;
    f->adaptcoeffs = f->historybuffer + order;

    memset(f->historybuffer, 0, (order * 2) * sizeof(*f->historybuffer));
    memset(f->coeffs, 0, order * sizeof(*f->coeffs));
    f->avg = 0;
}