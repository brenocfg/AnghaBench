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
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ uint32 ;
struct TYPE_4__ {int /*<<< orphan*/  packets; int /*<<< orphan*/  bytes; } ;
typedef  TYPE_1__ c_p_data ;
struct TYPE_5__ {int key_len; } ;
typedef  TYPE_2__ TME_DATA ;
typedef  int /*<<< orphan*/  MEM_TYPE ;

/* Variables and functions */
 scalar_t__ TME_SUCCESS ; 

uint32 count_packets(uint8 *block, uint32 pkt_size, TME_DATA *data, MEM_TYPE *mem_ex, uint8 *mem_data)
{
		
	c_p_data *counters=(c_p_data*)(block+data->key_len*4);

	counters->bytes+=pkt_size;
	counters->packets++;
	
	return TME_SUCCESS;

}