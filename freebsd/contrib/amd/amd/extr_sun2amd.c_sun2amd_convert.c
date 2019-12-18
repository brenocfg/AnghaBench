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
typedef  int /*<<< orphan*/  line_buff ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int INFO_MAX_LINE_LEN ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int /*<<< orphan*/  errno ; 
 int file_read_line (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,char*,char*) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int) ; 
 char* strchr (char*,char) ; 
 int strerror (int /*<<< orphan*/ ) ; 
 char* sun_entry2amd (char*,char*) ; 

__attribute__((used)) static int
sun2amd_convert(FILE *sun_in, FILE *amd_out)
{
  char line_buff[INFO_MAX_LINE_LEN], *tmp, *key, *entry;
  int pos, line = 0, retval = 1;

  /* just to be safe */
  memset(line_buff, 0, sizeof(line_buff));

  /* Read the input line by line and do the conversion. */
  while ((pos = file_read_line(line_buff, sizeof(line_buff), sun_in))) {
    line++;
    line_buff[pos - 1] = '\0';

    /* remove comments */
    if ((tmp = strchr(line_buff, '#')) != NULL) {
      *tmp = '\0';
    }

    /* find start of key */
    key = line_buff;
    while (*key != '\0' && isspace((unsigned char)*key)) {
      key++;
    }

    /* ignore blank lines */
    if (*key == '\0') {
      continue;
    }

    /* find the end of the key and NULL terminate */
    tmp = key;
    while (*tmp != '\0' && isspace((unsigned char)*tmp) == 0) {
      tmp++;
    }
    if (*tmp == '\0') {
      plog(XLOG_ERROR, "map line %d has no entry", line);
      goto err;
    }
    *tmp++ = '\0';
    if (*tmp == '\0') {
      plog(XLOG_ERROR, "map line %d has no entry", line);
      goto err;
    }
    entry = tmp;

    /* convert the sun entry to an amd entry */
    if ((tmp = sun_entry2amd(key, entry)) == NULL) {
      plog(XLOG_ERROR, "parse error on line %d", line);
      goto err;
    }

    if (fprintf(amd_out, "%s %s\n", key, tmp) < 0) {
      plog(XLOG_ERROR, "can't write to output stream: %s", strerror(errno));
      goto err;
    }

    /* just to be safe */
    memset(line_buff, 0, sizeof(line_buff));
  }

  /* success */
  retval = 0;

 err:
  return retval;
}