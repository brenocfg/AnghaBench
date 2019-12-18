#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__** pool; int /*<<< orphan*/  alloc_list; scalar_t__ allocated; int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int buffer_size; } ;

/* Variables and functions */
 size_t BUFFER_POOL_FIRST ; 
 int BUFFER_POOL_LAST ; 
 int BUFFER_POOL_MAX_ELEMENTS ; 
 TYPE_2__ buffers ; 
 void* hb_fifo_init (int,int) ; 
 int /*<<< orphan*/  hb_list_init () ; 
 int /*<<< orphan*/  hb_lock_init () ; 

void hb_buffer_pool_init( void )
{
    buffers.lock = hb_lock_init();
    buffers.allocated = 0;

#if defined(HB_BUFFER_DEBUG)
    buffers.alloc_list = hb_list_init();
#endif

#if !defined(HB_NO_BUFFER_POOL)
    /* we allocate pools for sizes 2^10 through 2^25. requests larger than
     * 2^25 will get passed through to malloc. */
    int i;

    // Create larger queue for 2^10 bucket since all allocations smaller than
    // 2^10 come from here.
    buffers.pool[BUFFER_POOL_FIRST] = hb_fifo_init(BUFFER_POOL_MAX_ELEMENTS*10, 1);
    buffers.pool[BUFFER_POOL_FIRST]->buffer_size = 1 << 10;

    /* requests smaller than 2^10 are satisfied from the 2^10 pool. */
    for ( i = 1; i < BUFFER_POOL_FIRST; ++i )
    {
        buffers.pool[i] = buffers.pool[BUFFER_POOL_FIRST];
    }
    for ( i = BUFFER_POOL_FIRST + 1; i <= BUFFER_POOL_LAST; ++i )
    {
        buffers.pool[i] = hb_fifo_init(BUFFER_POOL_MAX_ELEMENTS, 1);
        buffers.pool[i]->buffer_size = 1 << i;
    }
#endif
}