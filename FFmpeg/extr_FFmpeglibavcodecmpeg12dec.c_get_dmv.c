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
struct TYPE_3__ {int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 int get_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int get_dmv(MpegEncContext *s)
{
    if (get_bits1(&s->gb))
        return 1 - (get_bits1(&s->gb) << 1);
    else
        return 0;
}