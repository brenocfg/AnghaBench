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
typedef  int /*<<< orphan*/  cwd ;
typedef  int /*<<< orphan*/  buff ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getcwd (char*,int) ; 
 scalar_t__ is_good_char (char) ; 
 int /*<<< orphan*/  is_good_path (char*) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int search_gcda (char*,int) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

int main(int argc, char *argv[])
{
	char buff[1024], *p;
	char cwd[4096];
	FILE *f;
	int l, pos, pos1, old_len, cwd_len;

	if (argc != 2) return 1;

	getcwd(cwd, sizeof(cwd));
	cwd_len = strlen(cwd);
	if (cwd[cwd_len-1] != '/') {
		cwd[cwd_len++] = '/';
		cwd[cwd_len] = 0;
	}

	f = fopen(argv[1], "rb+");
	if (f == NULL) return 2;

	while (1)
	{
readnext:
		l = fread(buff, 1, sizeof(buff), f);
		if (l <= 16) break;

		pos = 0;
		while (pos < l)
		{
			pos1 = search_gcda(buff + pos, l - pos);
			if (pos1 < 0) {
				fseek(f, -6, SEEK_CUR);
				goto readnext;
			}
			pos += pos1;

			while (pos > 0 && is_good_char(buff[pos-1])) pos--;

			if (pos == 0) {
				fseek(f, -(sizeof(buff) + 16), SEEK_CUR);
				goto readnext;
			}

			// paths must start with /
			while (pos < l && buff[pos] != '/') pos++;
			p = buff + pos;
			old_len = strlen(p);

			if (!is_good_path(p)) {
				pos += old_len;
				continue;
			}

			if (strncmp(p, cwd, cwd_len) != 0) {
				printf("can't handle: %s\n", p);
				pos += old_len;
				continue;
			}

			memmove(p, p + cwd_len, old_len - cwd_len + 1);
			fseek(f, -(sizeof(buff) - pos), SEEK_CUR);
			fwrite(p, 1, old_len, f);
			goto readnext;
		}
	}

	fclose(f);

	return 0;
}