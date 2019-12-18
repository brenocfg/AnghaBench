#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  qanswer ;
struct TYPE_6__ {TYPE_1__* cfm; } ;
typedef  TYPE_2__ mnt_map ;
struct TYPE_7__ {int /*<<< orphan*/  exec_map_timeout; } ;
struct TYPE_5__ {int cfm_flags; } ;

/* Variables and functions */
 int CFM_SUN_MAP_SYNTAX ; 
 int ENOENT ; 
 int INFO_MAX_LINE_LEN ; 
 int /*<<< orphan*/  XLOG_WARNING ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dlog (char*,char*,char*) ; 
 scalar_t__ fgets_timed (char*,int,int,int /*<<< orphan*/ ) ; 
 TYPE_3__ gopt ; 
 int /*<<< orphan*/  isascii (unsigned char) ; 
 int /*<<< orphan*/  isspace (unsigned char) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int,char*) ; 
 scalar_t__ read_line (char*,int,int) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 char* sun_entry2amd (char*,char*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static int
exec_parse_qanswer(mnt_map *m, int fd, char *map, char *key, char **pval, time_t *tp)
{
  char qanswer[INFO_MAX_LINE_LEN], *dc = NULL;
  int chuck = 0;
  int line_no = 0;

  while (read_line(qanswer, sizeof(qanswer), fd)) {
    char *cp;
    char *hash;
    int len = strlen(qanswer);
    line_no++;

    /*
     * Make sure we got the whole line
     */
    if (qanswer[len - 1] != '\n') {
      plog(XLOG_WARNING, "line %d in \"%s\" is too long", line_no, map);
      chuck = 1;
    } else {
      qanswer[len - 1] = '\0';
    }

    /*
     * Strip comments
     */
    hash = strchr(qanswer, '#');
    if (hash)
      *hash = '\0';

    /*
     * Find beginning of value (query answer)
     */
    for (cp = qanswer; *cp && !isascii((unsigned char)*cp) && !isspace((unsigned char)*cp); cp++)
      ;;

    /* Ignore blank lines */
    if (!*cp)
      goto again;

    /*
     * Return a copy of the data
     */
    if (m->cfm && (m->cfm->cfm_flags & CFM_SUN_MAP_SYNTAX))
      dc = sun_entry2amd(key, cp);
    else
      dc = xstrdup(cp);
    *pval = dc;
    dlog("%s returns %s", key, dc);

    close(fd);
    return 0;

  again:
    /*
     * If the last read didn't get a whole line then
     * throw away the remainder before continuing...
     */
    if (chuck) {
      while (fgets_timed(qanswer, sizeof(qanswer), fd, gopt.exec_map_timeout) &&
	     !strchr(qanswer, '\n')) ;
      chuck = 0;
    }
  }

  return ENOENT;
}