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
struct weak_block {unsigned int erase_block_no; unsigned int max_erases; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NS_ERR (char*) ; 
 struct weak_block* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int simple_strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  weak_blocks ; 
 char* weakblocks ; 

__attribute__((used)) static int parse_weakblocks(void)
{
	char *w;
	int zero_ok;
	unsigned int erase_block_no;
	unsigned int max_erases;
	struct weak_block *wb;

	if (!weakblocks)
		return 0;
	w = weakblocks;
	do {
		zero_ok = (*w == '0' ? 1 : 0);
		erase_block_no = simple_strtoul(w, &w, 0);
		if (!zero_ok && !erase_block_no) {
			NS_ERR("invalid weakblocks.\n");
			return -EINVAL;
		}
		max_erases = 3;
		if (*w == ':') {
			w += 1;
			max_erases = simple_strtoul(w, &w, 0);
		}
		if (*w == ',')
			w += 1;
		wb = kzalloc(sizeof(*wb), GFP_KERNEL);
		if (!wb) {
			NS_ERR("unable to allocate memory.\n");
			return -ENOMEM;
		}
		wb->erase_block_no = erase_block_no;
		wb->max_erases = max_erases;
		list_add(&wb->list, &weak_blocks);
	} while (*w);
	return 0;
}