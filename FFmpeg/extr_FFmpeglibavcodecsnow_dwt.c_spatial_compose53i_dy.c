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
struct TYPE_3__ {int y; int /*<<< orphan*/ * b1; int /*<<< orphan*/ * b0; } ;
typedef  int /*<<< orphan*/  IDWTELEM ;
typedef  TYPE_1__ DWTCompose ;

/* Variables and functions */
 int avpriv_mirror (int,int) ; 
 int /*<<< orphan*/  horizontal_compose53i (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vertical_compose53iH0 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vertical_compose53iL0 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void spatial_compose53i_dy(DWTCompose *cs, IDWTELEM *buffer,
                                  IDWTELEM *temp, int width, int height,
                                  int stride)
{
    int y        = cs->y;
    IDWTELEM *b0 = cs->b0;
    IDWTELEM *b1 = cs->b1;
    IDWTELEM *b2 = buffer + avpriv_mirror(y + 1, height - 1) * stride;
    IDWTELEM *b3 = buffer + avpriv_mirror(y + 2, height - 1) * stride;

    if (y + 1 < (unsigned)height)
        vertical_compose53iL0(b1, b2, b3, width);
    if (y + 0 < (unsigned)height)
        vertical_compose53iH0(b0, b1, b2, width);

    if (y - 1 < (unsigned)height)
        horizontal_compose53i(b0, temp, width);
    if (y + 0 < (unsigned)height)
        horizontal_compose53i(b1, temp, width);

    cs->b0  = b2;
    cs->b1  = b3;
    cs->y  += 2;
}