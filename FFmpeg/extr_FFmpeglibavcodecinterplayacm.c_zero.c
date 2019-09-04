#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int rows; } ;
typedef  TYPE_1__ InterplayACMContext ;

/* Variables and functions */
 int /*<<< orphan*/  set_pos (TYPE_1__*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zero(InterplayACMContext *s, unsigned ind, unsigned col)
{
    unsigned i;

    for (i = 0; i < s->rows; i++)
        set_pos(s, i, col, 0);
    return 0;
}