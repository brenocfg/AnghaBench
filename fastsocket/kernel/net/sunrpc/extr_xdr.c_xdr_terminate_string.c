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
typedef  size_t u32 ;
struct xdr_buf {size_t const page_base; int /*<<< orphan*/ * pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_USER0 ; 
 char* kmap_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (char*,int /*<<< orphan*/ ) ; 

void
xdr_terminate_string(struct xdr_buf *buf, const u32 len)
{
	char *kaddr;

	kaddr = kmap_atomic(buf->pages[0], KM_USER0);
	kaddr[buf->page_base + len] = '\0';
	kunmap_atomic(kaddr, KM_USER0);
}