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
typedef  int uint32_t ;

/* Variables and functions */
#define  FDT_BEGIN_NODE 131 
#define  FDT_END 130 
#define  FDT_END_NODE 129 
#define  FDT_PROP 128 
 int MAX_LEVEL ; 
 char* fdt_get_name (void const*,int,int /*<<< orphan*/ *) ; 
 int fdt_next_tag (void const*,int,int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char const*) ; 

__attribute__((used)) static int list_subnodes(const void *blob, int node)
{
	int nextoffset;		/* next node offset from libfdt */
	uint32_t tag;		/* current tag */
	int level = 0;		/* keep track of nesting level */
	const char *pathp;
	int depth = 1;		/* the assumed depth of this node */

	while (level >= 0) {
		tag = fdt_next_tag(blob, node, &nextoffset);
		switch (tag) {
		case FDT_BEGIN_NODE:
			pathp = fdt_get_name(blob, node, NULL);
			if (level <= depth) {
				if (pathp == NULL)
					pathp = "/* NULL pointer error */";
				if (*pathp == '\0')
					pathp = "/";	/* root is nameless */
				if (level == 1)
					puts(pathp);
			}
			level++;
			if (level >= MAX_LEVEL) {
				printf("Nested too deep, aborting.\n");
				return 1;
			}
			break;
		case FDT_END_NODE:
			level--;
			if (level == 0)
				level = -1;		/* exit the loop */
			break;
		case FDT_END:
			return 1;
		case FDT_PROP:
			break;
		default:
			if (level <= depth)
				printf("Unknown tag 0x%08X\n", tag);
			return 1;
		}
		node = nextoffset;
	}
	return 0;
}