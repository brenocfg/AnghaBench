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
struct string_list {char* string; int tag; } ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__**) ; 
 int EOF ; 
 int SYM_NORMAL ; 
 struct string_list* copy_node (struct string_list*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__** symbol_type_name ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct string_list *read_node(FILE *f)
{
	char buffer[256];
	struct string_list node = {
		.string = buffer,
		.tag = SYM_NORMAL };
	int c;

	while ((c = fgetc(f)) != EOF) {
		if (c == ' ') {
			if (node.string == buffer)
				continue;
			break;
		} else if (c == '\n') {
			if (node.string == buffer)
				return NULL;
			ungetc(c, f);
			break;
		}
		if (node.string >= buffer + sizeof(buffer) - 1) {
			fprintf(stderr, "Token too long\n");
			exit(1);
		}
		*node.string++ = c;
	}
	if (node.string == buffer)
		return NULL;
	*node.string = 0;
	node.string = buffer;

	if (node.string[1] == '#') {
		int n;

		for (n = 0; n < ARRAY_SIZE(symbol_type_name); n++) {
			if (node.string[0] == symbol_type_name[n][0]) {
				node.tag = n;
				node.string += 2;
				return copy_node(&node);
			}
		}
		fprintf(stderr, "Unknown type %c\n", node.string[0]);
		exit(1);
	}
	return copy_node(&node);
}