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
struct TYPE_3__ {int size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ExtraSEI ;

/* Variables and functions */
 int copy_emulation_prev (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_sei_msg_bytes(const ExtraSEI* sei, int type){
    int copied_size;
    if (sei->size == 0)
        return 0;

    copied_size = -copy_emulation_prev(sei->data,
                                       sei->size,
                                       NULL,
                                       0,
                                       0);

    if ((sei->size % 255) == 0) //may result in an extra byte
        copied_size++;

    return copied_size + sei->size / 255 + 1 + type / 255 + 1;
}