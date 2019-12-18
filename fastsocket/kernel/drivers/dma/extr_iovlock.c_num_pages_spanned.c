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
struct iovec {scalar_t__ iov_base; scalar_t__ iov_len; } ;

/* Variables and functions */
 unsigned long PAGE_ALIGN (scalar_t__) ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 

__attribute__((used)) static int num_pages_spanned(struct iovec *iov)
{
	return
	((PAGE_ALIGN((unsigned long)iov->iov_base + iov->iov_len) -
	((unsigned long)iov->iov_base & PAGE_MASK)) >> PAGE_SHIFT);
}