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
struct TYPE_3__ {unsigned int x96_rand; } ;
typedef  TYPE_1__ DCACoreDecoder ;

/* Variables and functions */

__attribute__((used)) static int rand_x96(DCACoreDecoder *s)
{
    s->x96_rand = 1103515245U * s->x96_rand + 12345U;
    return (s->x96_rand & 0x7fffffff) - 0x40000000;
}