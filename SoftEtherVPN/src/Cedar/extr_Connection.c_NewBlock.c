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
typedef  int UINT ;
struct TYPE_3__ {int IsFlooding; int Size; int SizeofData; void* Buf; void* Compressed; scalar_t__ Param1; scalar_t__ Ttl; scalar_t__ PriorityQoS; } ;
typedef  TYPE_1__ BLOCK ;

/* Variables and functions */
 int CalcCompress (int) ; 
 int Compress (void*,int,void*,int) ; 
 void* FALSE ; 
 int /*<<< orphan*/  Free (void*) ; 
 int MAX_PACKET_SIZE ; 
 void* MallocFast (int) ; 
 void* TRUE ; 
 int Uncompress (void*,int,void*,int) ; 

BLOCK *NewBlock(void *data, UINT size, int compress)
{
	BLOCK *b;
	// Validate arguments
	if (data == NULL)
	{
		return NULL;
	}

	b = MallocFast(sizeof(BLOCK));

	b->IsFlooding = false;

	b->PriorityQoS = b->Ttl = b->Param1 = 0;

	if (compress == 0)
	{
		// Uncompressed
		b->Compressed = FALSE;
		b->Buf = data;
		b->Size = size;
		b->SizeofData = size;
	}
	else if (compress == 1)
	{
		UINT max_size;

		// Compressed
		b->Compressed = TRUE;
		max_size = CalcCompress(size);
		b->Buf = MallocFast(max_size);
		b->Size = Compress(b->Buf, max_size, data, size);
		b->SizeofData = size;

		// Discard old data block
		Free(data);
	}
	else
	{
		// Expand
		UINT max_size;

		b->Compressed = FALSE;
		max_size = MAX_PACKET_SIZE;
		b->Buf = MallocFast(max_size);
		b->Size = Uncompress(b->Buf, max_size, data, size);
		b->SizeofData = size;

		// Discard old data
		Free(data);
	}

	return b;
}