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
struct grave_page {unsigned int page_no; unsigned int max_reads; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NS_ERR (char*) ; 
 int /*<<< orphan*/  grave_pages ; 
 char* gravepages ; 
 struct grave_page* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int simple_strtoul (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_gravepages(void)
{
	char *g;
	int zero_ok;
	unsigned int page_no;
	unsigned int max_reads;
	struct grave_page *gp;

	if (!gravepages)
		return 0;
	g = gravepages;
	do {
		zero_ok = (*g == '0' ? 1 : 0);
		page_no = simple_strtoul(g, &g, 0);
		if (!zero_ok && !page_no) {
			NS_ERR("invalid gravepagess.\n");
			return -EINVAL;
		}
		max_reads = 3;
		if (*g == ':') {
			g += 1;
			max_reads = simple_strtoul(g, &g, 0);
		}
		if (*g == ',')
			g += 1;
		gp = kzalloc(sizeof(*gp), GFP_KERNEL);
		if (!gp) {
			NS_ERR("unable to allocate memory.\n");
			return -ENOMEM;
		}
		gp->page_no = page_no;
		gp->max_reads = max_reads;
		list_add(&gp->list, &grave_pages);
	} while (*g);
	return 0;
}