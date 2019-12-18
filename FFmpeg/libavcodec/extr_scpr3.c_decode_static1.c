#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int size; int* symbols; } ;
typedef  TYPE_1__ PixelModel3 ;

/* Variables and functions */
 int update_model1_to_2 (TYPE_1__*,int) ; 
 int update_model1_to_4 (TYPE_1__*,int) ; 
 int update_model1_to_5 (TYPE_1__*,int) ; 

__attribute__((used)) static int decode_static1(PixelModel3 *m, uint32_t val)
{
    uint32_t size;

    size = m->size;
    for (int i = 0; i < size; i++) {
        if (val == m->symbols[i]) {
            if (size <= 4)
                return update_model1_to_4(m, val);
            else
                return update_model1_to_5(m, val);
        }
    }

    if (size >= 14)
        return update_model1_to_2(m, val);

    m->symbols[size] = val;
    m->size++;
    return 0;
}