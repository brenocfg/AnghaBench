#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct table {unsigned int offset_max; int /*<<< orphan*/  gpu_prefix; } ;
struct offset {int dummy; } ;
struct TYPE_3__ {size_t rm_eo; size_t rm_so; } ;
typedef  TYPE_1__ regmatch_t ;
typedef  int /*<<< orphan*/  regex_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  REG_EXTENDED ; 
 int REG_NOMATCH ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpu_name ; 
 struct offset* offset_new (unsigned int) ; 
 scalar_t__ regcomp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int regexec (int /*<<< orphan*/ *,char*,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 void* strtol (char*,int /*<<< orphan*/ *,int) ; 
 int table_build (struct table*) ; 
 int /*<<< orphan*/  table_offset_add (struct table*,struct offset*) ; 

__attribute__((used)) static int parser_auth(struct table *t, const char *filename)
{
	FILE *file;
	regex_t mask_rex;
	regmatch_t match[4];
	char buf[1024];
	size_t end;
	int len;
	int done = 0;
	int r;
	unsigned o;
	struct offset *offset;
	char last_reg_s[10];
	int last_reg;

	if (regcomp
	    (&mask_rex, "(0x[0-9a-fA-F]*) *([_a-zA-Z0-9]*)", REG_EXTENDED)) {
		fprintf(stderr, "Failed to compile regular expression\n");
		return -1;
	}
	file = fopen(filename, "r");
	if (file == NULL) {
		fprintf(stderr, "Failed to open: %s\n", filename);
		return -1;
	}
	fseek(file, 0, SEEK_END);
	end = ftell(file);
	fseek(file, 0, SEEK_SET);

	/* get header */
	if (fgets(buf, 1024, file) == NULL) {
		fclose(file);
		return -1;
	}

	/* first line will contain the last register
	 * and gpu name */
	sscanf(buf, "%s %s", gpu_name, last_reg_s);
	t->gpu_prefix = gpu_name;
	last_reg = strtol(last_reg_s, NULL, 16);

	do {
		if (fgets(buf, 1024, file) == NULL) {
			fclose(file);
			return -1;
		}
		len = strlen(buf);
		if (ftell(file) == end)
			done = 1;
		if (len) {
			r = regexec(&mask_rex, buf, 4, match, 0);
			if (r == REG_NOMATCH) {
			} else if (r) {
				fprintf(stderr,
					"Error matching regular expression %d in %s\n",
					r, filename);
				fclose(file);
				return -1;
			} else {
				buf[match[0].rm_eo] = 0;
				buf[match[1].rm_eo] = 0;
				buf[match[2].rm_eo] = 0;
				o = strtol(&buf[match[1].rm_so], NULL, 16);
				offset = offset_new(o);
				table_offset_add(t, offset);
				if (o > t->offset_max)
					t->offset_max = o;
			}
		}
	} while (!done);
	fclose(file);
	if (t->offset_max < last_reg)
		t->offset_max = last_reg;
	return table_build(t);
}