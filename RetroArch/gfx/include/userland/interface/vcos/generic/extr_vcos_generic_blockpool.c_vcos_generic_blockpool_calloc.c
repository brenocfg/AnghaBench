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
struct TYPE_4__ {int /*<<< orphan*/  block_data_size; } ;
typedef  TYPE_1__ VCOS_BLOCKPOOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* vcos_generic_blockpool_alloc (TYPE_1__*) ; 

void *vcos_generic_blockpool_calloc(VCOS_BLOCKPOOL_T *pool)
{
   void* ret = vcos_generic_blockpool_alloc(pool);
   if (ret)
      memset(ret, 0, pool->block_data_size);
   return ret;
}