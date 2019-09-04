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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int uint32 ;
typedef  scalar_t__ uint16 ;
struct timeval {int dummy; } ;
struct time_conv {int dummy; } ;
struct TYPE_3__ {int key_len; int filled_blocks; int block_size; int /*<<< orphan*/ * lut_base_address; int /*<<< orphan*/ * last_found; int /*<<< orphan*/ * shared_memory_base_address; } ;
typedef  TYPE_1__ TME_DATA ;
typedef  int /*<<< orphan*/  RECORD ;
typedef  int /*<<< orphan*/  MEM_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_MEMORY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GET_TIME (struct timeval*,struct time_conv*) ; 
 int SW_ULONG_AT (int /*<<< orphan*/ *,int) ; 
 int SW_USHORT_AT (int /*<<< orphan*/ *,int) ; 
 int TME_ERROR ; 
 int TME_FALSE ; 
 int TME_TRUE ; 

uint32 bucket_lookup(uint8 *key, TME_DATA *data, MEM_TYPE *mem_ex, struct time_conv *time_ref)  
{
	uint32 value;
	uint32 i,j;
	int found=-1;
	uint32 blocks;
	uint32 block_size;
	uint8 *temp;
	if ((data->key_len!=1)&&  /*16 bit value*/
		(data->key_len!=2))   /*32 bit value*/
		return TME_ERROR;
	
	/*32 bit values*/
	blocks=data->filled_blocks-1;
	block_size=data->block_size;
	i=blocks/2; /*relative shift*/
	j=i;
	temp=data->shared_memory_base_address+block_size;

	if (data->key_len==2)
	{
		value=SW_ULONG_AT(key,0);
	
		if((value<SW_ULONG_AT(temp,0))||(value>SW_ULONG_AT(temp+block_size*(blocks-1),4)))
		{
			uint32 *key32=(uint32*) key;
			key32[0]=key32[1]=0;

			GET_TIME((struct timeval *)(data->shared_memory_base_address+8),time_ref);

			data->last_found=NULL;
			return TME_FALSE;
		}
			
		while(found==-1) /* search routine */
		{   
			i=(i==1)? 1:i>>1;
			if (SW_ULONG_AT(temp+block_size*j,0)>value)
				if (SW_ULONG_AT(temp+block_size*(j-1),4)<value)
					found=-2;
				else
					j-=i;
			else
				if (SW_ULONG_AT(temp+block_size*j,4)<value) 
					if (SW_ULONG_AT(temp+block_size*j,0)>value)
						found=-2;
					else
						j+=i;
				else found=j;
		}	
		if (found<0)
		{
			uint32 *key32=(uint32*) key;
			key32[0]=key32[1]=0;

			GET_TIME((struct timeval *)(data->shared_memory_base_address+8),time_ref);
			
			data->last_found=NULL;
			return TME_FALSE;
		}
	
		data->last_found=data->lut_base_address+found*sizeof(RECORD);

		COPY_MEMORY(key,temp+block_size*found,8);

		GET_TIME((struct timeval *)(temp+block_size*found+8),time_ref);

		return TME_TRUE;
	}
	else
	{
		value=SW_USHORT_AT(key,0);
	
		if((value<SW_USHORT_AT(temp,0))||(value>SW_USHORT_AT(temp+block_size*(blocks-1),2)))
		{
			uint16 *key16=(uint16*) key;
			key16[0]=key16[1]=0;
			
			GET_TIME((struct timeval *)(data->shared_memory_base_address+4),time_ref);

			data->last_found=NULL;
			return TME_FALSE;
		}
			
		while(found==-1) /* search routine */
		{   
			i=(i==1)? 1:i>>1;
			if (SW_USHORT_AT(temp+block_size*j,0)>value)
				if (SW_USHORT_AT(temp+block_size*(j-1),2)<value)
					found=-2;
				else
					j-=i;
			else
				if (SW_USHORT_AT(temp+block_size*j,2)<value) 
					if (SW_USHORT_AT(temp+block_size*j,0)>value)
						found=-2;
					else
						j+=i;
				else found=j;
		}	

		if (found<0)
		{
			uint16 *key16=(uint16*) key;
			key16[0]=key16[1]=0;

			GET_TIME((struct timeval *)(data->shared_memory_base_address+4),time_ref);

			data->last_found=NULL;
			return TME_FALSE;
		}
	
		data->last_found=data->lut_base_address+found*sizeof(RECORD);

		GET_TIME((struct timeval *)(temp+block_size*found+4),time_ref);

		COPY_MEMORY(key,temp+block_size*found,4);
		
		return TME_TRUE;
	}
		
}