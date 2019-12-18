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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/ * previous; int /*<<< orphan*/ * current; } ;
typedef  TYPE_1__ Hnm4VideoContext ;

/* Variables and functions */

__attribute__((used)) static void hnm_flip_buffers(Hnm4VideoContext *hnm)
{
    uint8_t *temp;

    temp          = hnm->current;
    hnm->current  = hnm->previous;
    hnm->previous = temp;
}