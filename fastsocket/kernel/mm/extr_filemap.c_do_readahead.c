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
struct file {int dummy; } ;
struct address_space {TYPE_1__* a_ops; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  pgoff_t ;
struct TYPE_2__ {int /*<<< orphan*/  readpage; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  force_page_cache_readahead (struct address_space*,struct file*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static ssize_t
do_readahead(struct address_space *mapping, struct file *filp,
	     pgoff_t index, unsigned long nr)
{
	if (!mapping || !mapping->a_ops || !mapping->a_ops->readpage)
		return -EINVAL;

	force_page_cache_readahead(mapping, filp, index, nr);
	return 0;
}