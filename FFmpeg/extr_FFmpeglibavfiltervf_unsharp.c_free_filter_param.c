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
struct TYPE_3__ {int steps_y; int /*<<< orphan*/ * sc; } ;
typedef  TYPE_1__ UnsharpFilterParam ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_filter_param(UnsharpFilterParam *fp)
{
    int z;

    for (z = 0; z < 2 * fp->steps_y; z++)
        av_freep(&fp->sc[z]);
}