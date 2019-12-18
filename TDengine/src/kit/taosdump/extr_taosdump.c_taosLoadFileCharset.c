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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  tfree (char*) ; 

void taosLoadFileCharset(FILE *fp, char *fcharset) {
  char * line = NULL;
  size_t line_size = 0;

  fseek(fp, 0, SEEK_SET);
  ssize_t size = getline(&line, &line_size, fp);
  if (size <= 2) {
    goto _exit_no_charset;
  }

  if (strncmp(line, "#!", 2) != 0) {
    goto _exit_no_charset;
  }
  if (line[size - 1] == '\n') {
    line[size - 1] = '\0';
    size--;
  }
  strcpy(fcharset, line + 2);

  tfree(line);
  return;

_exit_no_charset:
  fseek(fp, 0, SEEK_SET);
  *fcharset = '\0';
  tfree(line);
  return;
}