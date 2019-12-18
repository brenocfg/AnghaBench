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
struct TYPE_2__ {int /*<<< orphan*/  is_alloced; } ;

/* Variables and functions */
 scalar_t__ CACHE_BLOCKSIZE ; 
 TYPE_1__* s_ram_descriptor ; 
 int s_ramblockcnt ; 

size_t esp_himem_get_free_size(void)
{
    size_t ret=0;
    for (int i = 0; i < s_ramblockcnt; i++) {
        if (!s_ram_descriptor[i].is_alloced) ret+=CACHE_BLOCKSIZE;
    }
    return ret;
}