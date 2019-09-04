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
typedef  int uint32_t ;
struct TYPE_4__ {int size; int* symbols; } ;
typedef  TYPE_1__ PixelModel3 ;

/* Variables and functions */
 int update_model3_to_7 (TYPE_1__*,int) ; 

__attribute__((used)) static int decode_static3(PixelModel3 *m, uint32_t val)
{
    uint32_t size = m->size;

    for (int i = 0; i < size; i++) {
        if (val == m->symbols[i])
            return update_model3_to_7(m, val);
    }

    if (size >= 256)
        return 0;

    m->symbols[size] = val;
    m->size++;
    return 0;
}