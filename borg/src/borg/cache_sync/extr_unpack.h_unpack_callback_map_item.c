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
struct TYPE_3__ {int level; int expect; } ;
typedef  TYPE_1__ unpack_user ;

/* Variables and functions */
 int /*<<< orphan*/  SET_LAST_ERROR (char*) ; 
#define  expect_map_item_end 128 
 int expect_map_key ; 

__attribute__((used)) static inline int unpack_callback_map_item(unpack_user* u, unsigned int current)
{
    (void)u; (void)current;

    if(u->level == 1) {
        switch(u->expect) {
        case expect_map_item_end:
            u->expect = expect_map_key;
            break;
        default:
            SET_LAST_ERROR("Unexpected map item");
            return -1;
        }
    }
    return 0;
}