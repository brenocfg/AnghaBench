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
typedef  size_t uint32 ;
struct timeval {int dummy; } ;
struct time_conv {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/ * buffer; } ;
struct TYPE_7__ {scalar_t__ block; } ;
struct TYPE_6__ {size_t key_len; size_t lut_entries; size_t filled_entries; size_t rehashing_value; int /*<<< orphan*/ * last_found; scalar_t__ shared_memory_base_address; scalar_t__ lut_base_address; } ;
typedef  TYPE_1__ TME_DATA ;
typedef  TYPE_2__ RECORD ;
typedef  TYPE_3__ MEM_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  GET_TIME (struct timeval*,struct time_conv*) ; 
 int SW_ULONG_AT (scalar_t__*,int /*<<< orphan*/ ) ; 
 size_t TME_FALSE ; 
 size_t TME_TRUE ; 
 size_t ULONG_AT (int /*<<< orphan*/ *,size_t) ; 

uint32 normal_lut_wo_insert(uint8 *key, TME_DATA *data, MEM_TYPE *mem_ex, struct time_conv *time_ref) 
{
	uint32 i;
	uint32 tocs=0;
	uint32 *key32=(uint32*) key;
	uint32 shrinked_key=0;
	uint32 index;
	RECORD *records=(RECORD*)data->lut_base_address;
	uint8 *offset;
	uint32 key_len=data->key_len;
	/*the key is shrinked into a 32-bit value */	
	for (i=0; i<key_len;i++) 
		shrinked_key^=key32[i];
    /*the first index in the table is calculated*/
	index=shrinked_key % data->lut_entries;

	while (tocs<=data->filled_entries)
	{ 	

		if (records[index].block==0)
		{   /*out of table, insertion is not allowed*/
			GET_TIME((struct timeval *)(data->shared_memory_base_address+4*key_len),time_ref);
			data->last_found=NULL;	
			return TME_FALSE;
		}
		/*offset contains the absolute pointer to the block*/
		/*associated with the current entry */
		
		offset=mem_ex->buffer+SW_ULONG_AT(&records[index].block,0);		

		for (i=0; (i<key_len) && (key32[i]==ULONG_AT(offset,i*4)); i++);
		
		if (i==key_len)
			{
				/*key in the block matches the one provided, right entry*/
				GET_TIME((struct timeval *)(offset+4*key_len),time_ref);
				data->last_found=(uint8*)&records[index];
				return TME_TRUE;
			}
		else 
		{
			/*wrong entry, rehashing*/
			index=(index+data->rehashing_value) % data->lut_entries;
			tocs++;
		}
	}

	/*nothing found, last found= out of lut*/
	GET_TIME((struct timeval *)(data->shared_memory_base_address+4*key_len),time_ref);
	data->last_found=NULL;
	return TME_FALSE;

}