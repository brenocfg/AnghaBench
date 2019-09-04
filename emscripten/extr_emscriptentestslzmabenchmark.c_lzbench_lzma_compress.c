#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t int64_t ;
struct TYPE_5__ {size_t level; } ;
typedef  size_t SizeT ;
typedef  TYPE_1__ CLzmaEncProps ;

/* Variables and functions */
 size_t LZMA_PROPS_SIZE ; 
 int /*<<< orphan*/  LzmaEncProps_Init (TYPE_1__*) ; 
 int /*<<< orphan*/  LzmaEncProps_Normalize (TYPE_1__*) ; 
 int LzmaEncode (int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,size_t,TYPE_1__*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SZ_OK ; 
 int /*<<< orphan*/  g_Alloc ; 

int64_t lzbench_lzma_compress(char *inbuf, size_t insize, char *outbuf, size_t outsize, size_t level, size_t x, char* y)
{
	CLzmaEncProps props;
	int res;
    size_t headerSize = LZMA_PROPS_SIZE;
	SizeT out_len = outsize - LZMA_PROPS_SIZE;
	
	LzmaEncProps_Init(&props);
	props.level = level;
	LzmaEncProps_Normalize(&props);
  /*
  p->level = 5;
  p->dictSize = p->mc = 0;
  p->reduceSize = (UInt64)(Int64)-1;
  p->lc = p->lp = p->pb = p->algo = p->fb = p->btMode = p->numHashBytes = p->numThreads = -1;
  p->writeEndMark = 0;
  */
  
  	res = LzmaEncode((uint8_t*)outbuf+LZMA_PROPS_SIZE, &out_len, (uint8_t*)inbuf, insize, &props, (uint8_t*)outbuf, &headerSize, 0/*int writeEndMark*/, NULL, &g_Alloc, &g_Alloc);
	if (res != SZ_OK) return 0;
	
//	printf("out_len=%u LZMA_PROPS_SIZE=%d headerSize=%d\n", (int)(out_len + LZMA_PROPS_SIZE), LZMA_PROPS_SIZE, (int)headerSize);
	return LZMA_PROPS_SIZE + out_len;
}