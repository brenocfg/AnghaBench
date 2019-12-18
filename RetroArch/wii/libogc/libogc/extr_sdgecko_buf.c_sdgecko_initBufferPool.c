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
typedef  int u32 ;
struct TYPE_3__ {struct TYPE_3__* next; } ;

/* Variables and functions */
 int BUF_POOL_CNT ; 
 TYPE_1__* s_buf ; 
 TYPE_1__* s_freepool ; 

void sdgecko_initBufferPool()
{
	u32 i;
	for(i=0;i<BUF_POOL_CNT-1;++i) {
		s_buf[i].next = s_buf+i+1;
	}
	s_buf[i].next = NULL;
	s_freepool = s_buf;
}