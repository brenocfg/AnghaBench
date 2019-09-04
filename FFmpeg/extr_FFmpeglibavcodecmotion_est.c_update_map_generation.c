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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int map_generation; int /*<<< orphan*/  map; } ;
typedef  TYPE_1__ MotionEstContext ;

/* Variables and functions */
 int ME_MAP_MV_BITS ; 
 int ME_MAP_SIZE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline unsigned update_map_generation(MotionEstContext *c)
{
    c->map_generation+= 1<<(ME_MAP_MV_BITS*2);
    if(c->map_generation==0){
        c->map_generation= 1<<(ME_MAP_MV_BITS*2);
        memset(c->map, 0, sizeof(uint32_t)*ME_MAP_SIZE);
    }
    return c->map_generation;
}