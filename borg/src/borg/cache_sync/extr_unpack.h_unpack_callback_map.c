#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ csize; scalar_t__ size; } ;
struct TYPE_5__ {scalar_t__ level; scalar_t__ expect; scalar_t__ inside_chunks; TYPE_1__ item; scalar_t__ has_chunks; scalar_t__ part; } ;
typedef  TYPE_2__ unpack_user ;

/* Variables and functions */
 int /*<<< orphan*/  SET_LAST_ERROR (char*) ; 
 int /*<<< orphan*/  UNEXPECTED (char*) ; 
 scalar_t__ expect_item_begin ; 
 scalar_t__ expect_map_key ; 

__attribute__((used)) static inline int unpack_callback_map(unpack_user* u, unsigned int n)
{
    (void)n;

    if(u->level == 0) {
        if(u->expect != expect_item_begin) {
            SET_LAST_ERROR("Invalid state transition");  /* unreachable */
            return -1;
        }
        /* This begins a new Item */
        u->expect = expect_map_key;
        u->part = 0;
        u->has_chunks = 0;
        u->item.size = 0;
        u->item.csize = 0;
    }

    if(u->inside_chunks) {
        UNEXPECTED("map");
    }

    u->level++;

    return 0;
}