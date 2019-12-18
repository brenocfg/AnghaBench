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
struct range_box {int /*<<< orphan*/  color; } ;

/* Variables and functions */
 int FFDIFFSIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmp_color(const void *a, const void *b)
{
    const struct range_box *box1 = a;
    const struct range_box *box2 = b;
    return FFDIFFSIGN(box1->color , box2->color);
}