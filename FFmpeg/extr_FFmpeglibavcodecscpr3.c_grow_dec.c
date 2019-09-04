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
struct TYPE_3__ {int length; int /*<<< orphan*/ * cnts; } ;
typedef  TYPE_1__ PixelModel3 ;

/* Variables and functions */

__attribute__((used)) static void grow_dec(PixelModel3 *m)
{
    int a;

    a = 2 * m->length;
    m->cnts[2 * m->length] = m->cnts[m->length];
    m->length = a;
}