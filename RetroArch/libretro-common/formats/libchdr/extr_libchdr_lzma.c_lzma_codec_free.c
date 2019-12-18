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
struct TYPE_2__ {int /*<<< orphan*/  allocator; int /*<<< orphan*/  decoder; } ;
typedef  TYPE_1__ lzma_codec_data ;
typedef  int /*<<< orphan*/  lzma_allocator ;
typedef  int /*<<< orphan*/  ISzAlloc ;

/* Variables and functions */
 int /*<<< orphan*/  LzmaDec_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzma_allocator_free (int /*<<< orphan*/ *) ; 

void lzma_codec_free(void* codec)
{
	lzma_codec_data* lzma_codec = (lzma_codec_data*) codec;
	lzma_allocator* alloc = &lzma_codec->allocator;

	/* free memory */
	lzma_allocator_free(alloc);
	LzmaDec_Free(&lzma_codec->decoder, (ISzAlloc*)&lzma_codec->allocator);
}