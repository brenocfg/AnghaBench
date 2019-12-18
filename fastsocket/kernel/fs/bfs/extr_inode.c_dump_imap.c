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
struct super_block {int dummy; } ;
struct TYPE_2__ {int si_lasti; int /*<<< orphan*/  si_imap; } ;

/* Variables and functions */
 TYPE_1__* BFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*,int,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

void dump_imap(const char *prefix, struct super_block *s)
{
#ifdef DEBUG
	int i;
	char *tmpbuf = (char *)get_zeroed_page(GFP_KERNEL);

	if (!tmpbuf)
		return;
	for (i = BFS_SB(s)->si_lasti; i >= 0; i--) {
		if (i > PAGE_SIZE - 100) break;
		if (test_bit(i, BFS_SB(s)->si_imap))
			strcat(tmpbuf, "1");
		else
			strcat(tmpbuf, "0");
	}
	printf("BFS-fs: %s: lasti=%08lx <%s>\n",
				prefix, BFS_SB(s)->si_lasti, tmpbuf);
	free_page((unsigned long)tmpbuf);
#endif
}