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
typedef  int /*<<< orphan*/  u64 ;
struct badblocks {scalar_t__ shift; int count; int /*<<< orphan*/  lock; scalar_t__ unacked_exist; int /*<<< orphan*/ * page; } ;
typedef  size_t ssize_t ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int BB_ACK (int /*<<< orphan*/ ) ; 
 unsigned int BB_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ BB_OFFSET (int /*<<< orphan*/ ) ; 
 size_t PAGE_SIZE ; 
 unsigned int read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ snprintf (char*,size_t,char*,unsigned long long,unsigned int) ; 

__attribute__((used)) static ssize_t
badblocks_show(struct badblocks *bb, char *page, int unack)
{
	size_t len;
	int i;
	u64 *p = bb->page;
	unsigned seq;

	if (bb->shift < 0)
		return 0;

retry:
	seq = read_seqbegin(&bb->lock);

	len = 0;
	i = 0;

	while (len < PAGE_SIZE && i < bb->count) {
		sector_t s = BB_OFFSET(p[i]);
		unsigned int length = BB_LEN(p[i]);
		int ack = BB_ACK(p[i]);
		i++;

		if (unack && ack)
			continue;

		len += snprintf(page+len, PAGE_SIZE-len, "%llu %u\n",
				(unsigned long long)s << bb->shift,
				length << bb->shift);
	}
	if (unack && len == 0)
		bb->unacked_exist = 0;

	if (read_seqretry(&bb->lock, seq))
		goto retry;

	return len;
}