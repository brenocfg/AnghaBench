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
struct page {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext3_get_block ; 
 int mpage_readpage (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ext3_readpage (struct page*) ; 

__attribute__((used)) static int ext3_readpage(struct file *file, struct page *page)
{
	trace_ext3_readpage(page);
	return mpage_readpage(page, ext3_get_block);
}