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
typedef  int /*<<< orphan*/  hb_fifo_t ;
struct TYPE_2__ {int /*<<< orphan*/ ** pool; } ;

/* Variables and functions */
 int BUFFER_POOL_FIRST ; 
 int BUFFER_POOL_LAST ; 
 TYPE_1__ buffers ; 

__attribute__((used)) static hb_fifo_t *size_to_pool( int size )
{
#if !defined(HB_NO_BUFFER_POOL)
    int i;
    for ( i = BUFFER_POOL_FIRST; i <= BUFFER_POOL_LAST; ++i )
    {
        if ( size <= (1 << i) )
        {
            return buffers.pool[i];
        }
    }
#endif
    return NULL;
}