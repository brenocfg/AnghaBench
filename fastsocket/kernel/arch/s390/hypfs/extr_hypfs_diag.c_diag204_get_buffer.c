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
typedef  enum diag204_format { ____Placeholder_diag204_format } diag204_format ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ INFO_EXT ; 
 int INFO_SIMPLE ; 
 scalar_t__ SUBC_RSI ; 
 int diag204 (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* diag204_alloc_rbuf () ; 
 void* diag204_alloc_vbuf (int) ; 
 void* diag204_buf ; 
 int diag204_buf_pages ; 

__attribute__((used)) static void *diag204_get_buffer(enum diag204_format fmt, int *pages)
{
	if (diag204_buf) {
		*pages = diag204_buf_pages;
		return diag204_buf;
	}
	if (fmt == INFO_SIMPLE) {
		*pages = 1;
		return diag204_alloc_rbuf();
	} else {/* INFO_EXT */
		*pages = diag204((unsigned long)SUBC_RSI |
				 (unsigned long)INFO_EXT, 0, NULL);
		if (*pages <= 0)
			return ERR_PTR(-ENOSYS);
		else
			return diag204_alloc_vbuf(*pages);
	}
}