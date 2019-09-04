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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  start ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DEFFILEMODE ; 
 int /*<<< orphan*/  EX_NOINPUT ; 
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int O_CREAT ; 
 int O_EXLOCK ; 
 int O_RDWR ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 char* escape_string (char*) ; 
 int fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int fputs (char*,int /*<<< orphan*/ *) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fseeko (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int fstat (int,struct stat*) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int open (char const*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char * argv[])
{
	struct stat sb;
	int ret;
	int dstfd;
	FILE *dst = NULL;
	const char *json_output = NULL;
	const char *cwd = NULL;
	const char *input_file = NULL;
	char start[2];
	size_t read_bytes;
	int i;
	size_t input_file_len;

	if (argc < 5) {
		usage();
	}

	json_output = argv[1];
	cwd = argv[2];
	input_file = argv[3];

	argv += 4;
	argc -= 4;

	input_file_len = strlen(input_file);
	if (!(input_file_len > 2 && 0 == strcmp(".c",   input_file + input_file_len - 2)) &&
		!(input_file_len > 3 && 0 == strcmp(".cp",  input_file + input_file_len - 3)) &&
		!(input_file_len > 4 && 0 == strcmp(".cpp", input_file + input_file_len - 4))) {
		/* Not a C/C++ file, just skip it */
		return 0;
	}

	dstfd = open(json_output, O_RDWR | O_CREAT | O_EXLOCK, DEFFILEMODE);
	if (dstfd < 0)
		err(EX_NOINPUT, "open(%s)", json_output);

	ret = fstat(dstfd, &sb);
	if (ret < 0)
		err(EX_NOINPUT, "fstat(%s)", json_output);

	if (!S_ISREG(sb.st_mode))
		err(EX_USAGE, "%s is not a regular file", json_output);

	dst = fdopen(dstfd, "w+");
	if (dst == NULL)
		err(EX_UNAVAILABLE, "fdopen");

	read_bytes = fread(start, sizeof(start[0]), sizeof(start)/sizeof(start[0]), dst);
	if ((read_bytes != sizeof(start)) || (0 != memcmp(start, "[\n", sizeof(start)/sizeof(start[0])))) {
		/* no JSON start, we don't really care why */
		ret = fseeko(dst, 0, SEEK_SET);
		if (ret < 0)
			err(EX_UNAVAILABLE, "fseeko");

		ret = fputs("[", dst);
		if (ret < 0)
			err(EX_UNAVAILABLE, "fputs");
	} else {
		/* has at least two bytes at the start. Seek to 3 bytes before the end */
		ret = fseeko(dst, -3, SEEK_END);
		if (ret < 0)
			err(EX_UNAVAILABLE, "fseeko");

		ret = fputs(",", dst);
		if (ret < 0)
			err(EX_UNAVAILABLE, "fputs");
	}

	fprintf(dst, "\n");
	fprintf(dst, "{\n");
	fprintf(dst, "  \"directory\": \"%s\",\n", cwd);
	fprintf(dst, "  \"file\": \"%s\",\n", input_file);
	fprintf(dst, "  \"command\": \"");
	for (i=0; i < argc; i++) {
		bool needs_escape = strchr(argv[i], '\\') || strchr(argv[i], '"') || strchr(argv[i], ' ');
		
		if (needs_escape) {
			char *escaped_string = escape_string(argv[i]);
			fprintf(dst, "%s\\\"%s\\\"", i == 0 ? "" : " ", escaped_string);
			free(escaped_string);
		} else {
			fprintf(dst, "%s%s", i == 0 ? "" : " ", argv[i]);
		}
	}
	fprintf(dst, "\"\n");
	fprintf(dst, "}\n");
	fprintf(dst, "]\n");

	ret = fclose(dst);
	if (ret < 0)
		err(EX_UNAVAILABLE, "fclose");

	return 0;
}