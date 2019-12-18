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
struct TYPE_2__ {int /*<<< orphan*/  Free; int /*<<< orphan*/  Alloc; int /*<<< orphan*/  allocptr; } ;
typedef  TYPE_1__ lzma_allocator ;

/* Variables and functions */
 int /*<<< orphan*/  lzma_fast_alloc ; 
 int /*<<< orphan*/  lzma_fast_free ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void lzma_allocator_init(void* p)
{
	lzma_allocator *codec = (lzma_allocator *)(p);

	/* reset pointer list */
	memset(codec->allocptr, 0, sizeof(codec->allocptr));
	codec->Alloc = lzma_fast_alloc;
	codec->Free = lzma_fast_free;
}