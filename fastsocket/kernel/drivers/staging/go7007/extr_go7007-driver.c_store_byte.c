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
typedef  int /*<<< orphan*/  u8 ;
struct go7007_buffer {scalar_t__ bytesused; unsigned int offset; int /*<<< orphan*/ * pages; } ;

/* Variables and functions */
 scalar_t__ GO7007_BUF_SIZE ; 
 unsigned int PAGE_MASK ; 
 unsigned int PAGE_SHIFT ; 
 scalar_t__ page_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void store_byte(struct go7007_buffer *gobuf, u8 byte)
{
	if (gobuf != NULL && gobuf->bytesused < GO7007_BUF_SIZE) {
		unsigned int pgidx = gobuf->offset >> PAGE_SHIFT;
		unsigned int pgoff = gobuf->offset & ~PAGE_MASK;

		*((u8 *)page_address(gobuf->pages[pgidx]) + pgoff) = byte;
		++gobuf->offset;
		++gobuf->bytesused;
	}
}