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
struct node {int dummy; } ;
typedef  enum op { ____Placeholder_op } op ;
typedef  enum gen_funcs { ____Placeholder_gen_funcs } gen_funcs ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int GEN_FUNCS_C ; 
 int GEN_FUNCS_H ; 
 int GEN_FUNCS_NONE ; 
 scalar_t__ MAXPATHLEN ; 
#define  OP_ENUMS 131 
#define  OP_EXTRACT 130 
#define  OP_GEN 129 
#define  OP_TREE 128 
 int TOK_EOF ; 
 int /*<<< orphan*/  check_tree (struct node*) ; 
 int debug ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 char* file_prefix ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  gen_extract (int /*<<< orphan*/ ,struct node*,char*) ; 
 int /*<<< orphan*/  gen_tree (struct node*,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int gettoken () ; 
 int /*<<< orphan*/  input_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int localincs ; 
 int /*<<< orphan*/  make_enums (int,char**,int) ; 
 int /*<<< orphan*/  make_table (struct node*,int) ; 
 int /*<<< orphan*/  merge (struct node**,struct node*) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 struct node* parse_top (int) ; 
 int /*<<< orphan*/  path_new (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strlen (char*) ; 
 char* usgtxt ; 

int
main(int argc, char *argv[])
{
	enum op op = OP_GEN;
	enum gen_funcs gen_funcs = GEN_FUNCS_NONE;

	char *infile = NULL;

	int opt;
	while ((opt = getopt(argc, argv, "dEeFfhI:i:lp:t")) != EOF)
		switch (opt) {

		  case 'd':
			debug = 1;
			break;

		  case 'E':
			if (op != OP_GEN && op != OP_ENUMS)
				errx(1, "-E conflicts with earlier options");
			op = OP_ENUMS;
			break;

		  case 'e':
			if (op != OP_GEN && op != OP_EXTRACT)
				errx(1, "-e conflicts with earlier options");
			op = OP_EXTRACT;
			break;

		  case 'F':
			if (gen_funcs != GEN_FUNCS_NONE &&
			    gen_funcs != GEN_FUNCS_C)
				errx(1, "-F conflicts with -f");
			gen_funcs = GEN_FUNCS_C;
			break;

		  case 'f':
			if (gen_funcs != GEN_FUNCS_NONE &&
			    gen_funcs != GEN_FUNCS_H)
				errx(1, "-f conflicts with -F");
			gen_funcs = GEN_FUNCS_H;
			break;

		  case 'h':
			fprintf(stderr, "%s", usgtxt);
			exit(0);

		  case 'I':
			path_new(optarg);
			break;

		  case 'i':
			infile = optarg;
			break;

		  case 'l':
			localincs = 1;
			break;

		  case 'p':
			file_prefix = optarg;
			if (strlen(file_prefix) + strlen("tree.c") >
			    MAXPATHLEN)
				errx(1, "prefix too long");
			break;

		  case 't':
			if (op != OP_GEN && op != OP_TREE)
				errx(1, "-t conflicts with earlier options");
			op = OP_TREE;
			break;
		}

	argc -= optind;
	argv += optind;

	/* open input */
	if (infile == NULL) {
		input_new(stdin, NULL, "<stdin>");
	} else {
		FILE *fp;
		if ((fp = fopen(infile, "r")) == NULL)
			err(1, "%s", infile);
		input_new(fp, NULL, infile);
	}

	/* parse and check input */
	struct node *root = parse_top(gettoken());

	int tok;
	while ((tok = gettoken()) != TOK_EOF)
		merge(&root, parse_top(tok));

	if (root)
		check_tree(root);

	/* do what the user has requested */
	switch (op) {

	  case OP_EXTRACT:
		if (argc == 0)
			errx(1, "-e requires arguments");

		for (int i = 0; i < argc; i++)
			if (gen_extract(stdout, root, argv[i]))
				errx(1, "object not found: %s", argv[i]);
		return (0);

	  case OP_ENUMS:
		make_enums(argc, argv, gen_funcs);
		return (0);

	  case OP_TREE:
		if (argc != 0)
			errx(1, "-t allows no arguments");
		gen_tree(root, 0);
		return (0);

	  case OP_GEN:
		if (argc != 0)
			errx(1, "tree generation allows no arguments");
		make_table(root, gen_funcs == GEN_FUNCS_H);
		return (0);
	}
}