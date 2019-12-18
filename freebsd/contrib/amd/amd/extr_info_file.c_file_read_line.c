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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ferror (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int getc (int /*<<< orphan*/ *) ; 
 scalar_t__ isascii (unsigned char) ; 
 scalar_t__ isspace (unsigned char) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 

int
file_read_line(char *buf, int size, FILE *fp)
{
  int done = 0;

  do {
    while (fgets(buf, size, fp)) {
      int len = strlen(buf);
      done += len;
      if (len > 1 && buf[len - 2] == '\\' &&
	  buf[len - 1] == '\n') {
	int ch;
	buf += len - 2;
	size -= len - 2;
	*buf = '\n';
	buf[1] = '\0';
	/*
	 * Skip leading white space on next line
	 */
	while ((ch = getc(fp)) != EOF &&
	       isascii((unsigned char)ch) && isspace((unsigned char)ch)) ;
	(void) ungetc(ch, fp);
      } else {
	return done;
      }
    }
  } while (size > 0 && !feof(fp) && !ferror(fp));

  return done;
}