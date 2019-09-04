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

/* Variables and functions */
 size_t AV_INPUT_BUFFER_PADDING_SIZE ; 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_fast_malloc (int /*<<< orphan*/ **,unsigned int*,size_t,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

void av_fast_padded_mallocz(void *ptr, unsigned int *size, size_t min_size)
{
    uint8_t **p = ptr;
    if (min_size > SIZE_MAX - AV_INPUT_BUFFER_PADDING_SIZE) {
        av_freep(p);
        *size = 0;
        return;
    }
    if (!ff_fast_malloc(p, size, min_size + AV_INPUT_BUFFER_PADDING_SIZE, 1))
        memset(*p, 0, min_size + AV_INPUT_BUFFER_PADDING_SIZE);
}