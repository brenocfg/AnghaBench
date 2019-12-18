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
struct file_ra_state {int start; int /*<<< orphan*/  size; int /*<<< orphan*/  async_size; } ;
struct address_space {int dummy; } ;
typedef  int pgoff_t ;

/* Variables and functions */
 int count_history_pages (struct address_space*,struct file_ra_state*,int,unsigned long) ; 
 int /*<<< orphan*/  get_init_ra_size (int,unsigned long) ; 

__attribute__((used)) static int try_context_readahead(struct address_space *mapping,
				 struct file_ra_state *ra,
				 pgoff_t offset,
				 unsigned long req_size,
				 unsigned long max)
{
	pgoff_t size;

	size = count_history_pages(mapping, ra, offset, max);

	/*
	 * no history pages:
	 * it could be a random read
	 */
	if (!size)
		return 0;

	/*
	 * starts from beginning of file:
	 * it is a strong indication of long-run stream (or whole-file-read)
	 */
	if (size >= offset)
		size *= 2;

	ra->start = offset;
	ra->size = get_init_ra_size(size + req_size, max);
	ra->async_size = ra->size;

	return 1;
}