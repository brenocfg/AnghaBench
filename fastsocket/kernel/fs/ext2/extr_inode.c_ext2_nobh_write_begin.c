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
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ext2_get_block ; 
 int nobh_write_begin (struct file*,struct address_space*,int /*<<< orphan*/ ,unsigned int,unsigned int,struct page**,void**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ext2_nobh_write_begin(struct file *file, struct address_space *mapping,
		loff_t pos, unsigned len, unsigned flags,
		struct page **pagep, void **fsdata)
{
	/*
	 * Dir-in-pagecache still uses ext2_write_begin. Would have to rework
	 * directory handling code to pass around offsets rather than struct
	 * pages in order to make this work easily.
	 */
	return nobh_write_begin(file, mapping, pos, len, flags, pagep, fsdata,
							ext2_get_block);
}