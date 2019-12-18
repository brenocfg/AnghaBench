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
struct stat {int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_size; } ;
struct property {int dummy; } ;
struct node {int dummy; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_child (struct node*,struct node*) ; 
 int /*<<< orphan*/  add_property (struct node*,struct property*) ; 
 struct node* build_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct property* build_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  data_copy_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*,char const*,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* join_path (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 struct node* name_node (struct node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ streq (int /*<<< orphan*/ ,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct node *read_fstree(const char *dirname)
{
	DIR *d;
	struct dirent *de;
	struct stat st;
	struct node *tree;

	d = opendir(dirname);
	if (!d)
		die("Couldn't opendir() \"%s\": %s\n", dirname, strerror(errno));

	tree = build_node(NULL, NULL);

	while ((de = readdir(d)) != NULL) {
		char *tmpnam;

		if (streq(de->d_name, ".")
		    || streq(de->d_name, ".."))
			continue;

		tmpnam = join_path(dirname, de->d_name);

		if (lstat(tmpnam, &st) < 0)
			die("stat(%s): %s\n", tmpnam, strerror(errno));

		if (S_ISREG(st.st_mode)) {
			struct property *prop;
			FILE *pfile;

			pfile = fopen(tmpnam, "r");
			if (! pfile) {
				fprintf(stderr,
					"WARNING: Cannot open %s: %s\n",
					tmpnam, strerror(errno));
			} else {
				prop = build_property(strdup(de->d_name),
						      data_copy_file(pfile,
								     st.st_size),
						      NULL);
				add_property(tree, prop);
				fclose(pfile);
			}
		} else if (S_ISDIR(st.st_mode)) {
			struct node *newchild;

			newchild = read_fstree(tmpnam);
			newchild = name_node(newchild, strdup(de->d_name),
					     NULL);
			add_child(tree, newchild);
		}

		free(tmpnam);
	}

	return tree;
}