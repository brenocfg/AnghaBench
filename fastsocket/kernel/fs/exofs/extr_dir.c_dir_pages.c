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
struct inode {int i_size; } ;

/* Variables and functions */
 int PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 

__attribute__((used)) static inline unsigned long dir_pages(struct inode *inode)
{
	return (inode->i_size + PAGE_CACHE_SIZE - 1) >> PAGE_CACHE_SHIFT;
}