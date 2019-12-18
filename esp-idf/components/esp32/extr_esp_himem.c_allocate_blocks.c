#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_2__ {int is_alloced; int is_mapped; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* s_ram_descriptor ; 
 int s_ramblockcnt ; 

__attribute__((used)) static bool allocate_blocks(int count, uint16_t *blocks_out)
{
    int n = 0;
    for (int i = 0; i < s_ramblockcnt && n != count; i++) {
        if (!s_ram_descriptor[i].is_alloced) {
            blocks_out[n] = i;
            n++;
        }
    }
    if (n == count) {
        //All blocks could be allocated. Mark as in use.
        for (int i = 0; i < count; i++) {
            s_ram_descriptor[blocks_out[i]].is_alloced = true;
            assert(s_ram_descriptor[blocks_out[i]].is_mapped == false);
        }
        return true;
    } else {
        //Error allocating blocks
        return false;
    }
}