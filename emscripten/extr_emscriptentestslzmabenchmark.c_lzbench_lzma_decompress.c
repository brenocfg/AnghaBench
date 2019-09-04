#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int64_t ;
typedef  int SizeT ;
typedef  int /*<<< orphan*/  ELzmaStatus ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_FINISH_END ; 
 int LZMA_PROPS_SIZE ; 
 int LzmaDecode (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SZ_OK ; 
 int /*<<< orphan*/  g_Alloc ; 

int64_t lzbench_lzma_decompress(char *inbuf, size_t insize, char *outbuf, size_t outsize, size_t x, size_t y, char* z)
{
	int res;
	SizeT out_len = outsize;
	SizeT src_len = insize - LZMA_PROPS_SIZE;
	ELzmaStatus status;
	
//	SRes LzmaDecode(Byte *dest, SizeT *destLen, const Byte *src, SizeT *srcLen, const Byte *propData, unsigned propSize, ELzmaFinishMode finishMode, ELzmaStatus *status, ISzAlloc *alloc)
	res = LzmaDecode((uint8_t*)outbuf, &out_len, (uint8_t*)inbuf+LZMA_PROPS_SIZE, &src_len, (uint8_t*)inbuf, LZMA_PROPS_SIZE, LZMA_FINISH_END, &status, &g_Alloc);
	if (res != SZ_OK) return 0;
	
//	printf("out_len=%u\n", (int)(out_len + LZMA_PROPS_SIZE));	
    return out_len;
}