#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ uint32 ;
typedef  scalar_t__ uint16 ;
struct timeval {int dummy; } ;
struct time_conv {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/ * buffer; } ;
struct TYPE_7__ {int /*<<< orphan*/  exec_fcn; int /*<<< orphan*/  block; } ;
struct TYPE_6__ {int key_len; int filled_entries; int filled_blocks; int shared_memory_blocks; int lut_entries; int block_size; int default_exec; int /*<<< orphan*/ * shared_memory_base_address; scalar_t__ lut_base_address; } ;
typedef  TYPE_1__ TME_DATA ;
typedef  TYPE_2__ RECORD ;
typedef  TYPE_3__ MEM_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_MEMORY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GET_TIME (struct timeval*,struct time_conv*) ; 
 int /*<<< orphan*/  SW_ULONG_ASSIGN (int /*<<< orphan*/ *,int) ; 
 int SW_ULONG_AT (int /*<<< orphan*/ *,int) ; 
 scalar_t__ SW_USHORT_AT (int /*<<< orphan*/ *,int) ; 
 scalar_t__ TME_ERROR ; 
 scalar_t__ TME_TRUE ; 

uint32 bucket_lookup_insert(uint8 *key, TME_DATA *data, MEM_TYPE *mem_ex, struct time_conv *time_ref)   
{	
	RECORD *records=(RECORD*)data->lut_base_address;

	if ((data->key_len!=1)&&  /*16 bit value*/
		(data->key_len!=2))   /*32 bit value*/
		return TME_ERROR;

	if(data->key_len==2)
	{
		uint32 start,stop;
		uint8 *tmp;

		start=SW_ULONG_AT(key,0);	
		stop=SW_ULONG_AT(key,4);

		if (start>stop)
			return TME_ERROR;
		if (data->filled_entries>0)
		{
			tmp=mem_ex->buffer+SW_ULONG_AT(&records[data->filled_entries-1].block,0);		
			/*check if it is coherent with the previous block*/
			if (SW_ULONG_AT(tmp,4)>=start)
				return TME_ERROR;
		}
		
		if (data->filled_blocks==data->shared_memory_blocks)
			return TME_ERROR;

		if (data->filled_entries==data->lut_entries)
			return TME_ERROR;

		tmp=data->shared_memory_base_address+data->block_size*data->filled_blocks;		
		
		COPY_MEMORY(tmp,key,8);
		
		SW_ULONG_ASSIGN(&records[data->filled_entries].block,tmp-mem_ex->buffer);
		SW_ULONG_ASSIGN(&records[data->filled_entries].exec_fcn,data->default_exec);
		
		GET_TIME((struct timeval *)(tmp+8),time_ref);		
		
		data->filled_blocks++;
		data->filled_entries++;
		
		return TME_TRUE;
	}
	else
	{
		uint16 start,stop;
		uint8 *tmp;

		start=SW_USHORT_AT(key,0);	
		stop=SW_USHORT_AT(key,2);

		if (start>stop)
			return TME_ERROR;
		if (data->filled_entries>0)
		{
			tmp=mem_ex->buffer+SW_ULONG_AT(&records[data->filled_entries-1].block,0);		
			/*check if it is coherent with the previous block*/
			if (SW_USHORT_AT(tmp,2)>=start)
				return TME_ERROR;
		}
		
		if (data->filled_blocks==data->shared_memory_blocks)
			return TME_ERROR;

		if (data->filled_entries==data->lut_entries)
			return TME_ERROR;

		tmp=mem_ex->buffer+SW_ULONG_AT(&records[data->filled_entries].block,0);		
		
		COPY_MEMORY(tmp,key,4);
		
		SW_ULONG_ASSIGN(&records[data->filled_entries].block,tmp-mem_ex->buffer);
		SW_ULONG_ASSIGN(&records[data->filled_entries].exec_fcn,data->default_exec);
		
		GET_TIME((struct timeval *)(tmp+4),time_ref);		
		
		data->filled_blocks++;
		data->filled_entries++;
		
		return TME_TRUE;
	}
}