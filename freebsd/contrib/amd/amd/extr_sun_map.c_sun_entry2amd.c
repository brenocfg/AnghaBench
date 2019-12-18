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
struct sun_entry {int /*<<< orphan*/ * fstype; int /*<<< orphan*/ * mountpt_list; int /*<<< orphan*/ * opt_list; } ;
typedef  int /*<<< orphan*/  line_buff ;

/* Variables and functions */
 int INFO_MAX_LINE_LEN ; 
 scalar_t__ NSTREQ (int /*<<< orphan*/ *,char*,int) ; 
 char* SUN_AUTOFS_TYPE ; 
 char* SUN_CACHEFS_TYPE ; 
 char* SUN_HSFS_TYPE ; 
 char* SUN_NFS_TYPE ; 
 int /*<<< orphan*/  XFREE (struct sun_entry*) ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,...) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  sun_hsfs2amd (char*,int,char const*,struct sun_entry*) ; 
 struct sun_entry* sun_map_parse_read (char*) ; 
 int /*<<< orphan*/  sun_multi2amd (char*,int,char const*,struct sun_entry*) ; 
 int /*<<< orphan*/  sun_nfs2amd (char*,int,char const*,struct sun_entry*) ; 
 int /*<<< orphan*/  sun_opts2amd (char*,int,char const*,int /*<<< orphan*/ *) ; 
 char* xstrdup (char*) ; 
 int /*<<< orphan*/  xstrlcpy (char*,char const*,int) ; 

char *
sun_entry2amd(const char *key, const char *s_entry_str)
{
  char *retval = NULL;
  char line_buff[INFO_MAX_LINE_LEN];
  int ws;
  struct sun_entry *s_entry = NULL;

  /* The key should not be NULL. */
  if (key == NULL) {
    plog(XLOG_ERROR,"Sun key value was null");
    goto err;
  }
  /* The Sun entry string should never be NULL. */
  if (s_entry_str == NULL) {
    plog(XLOG_ERROR,"Sun entry value was null");
    goto err;
  }

  /* Make sure there are no trailing white spaces or '\n'. */
  xstrlcpy(line_buff, s_entry_str, sizeof(line_buff));
  ws = strlen(line_buff) - 1;
  while (ws >= 0 && (isspace((unsigned char)line_buff[ws]) || line_buff[ws] == '\n')) {
    line_buff[ws--] = '\0';
  }

  /* Parse the sun entry line. */
  s_entry = sun_map_parse_read(line_buff);
  if (s_entry == NULL) {
    plog(XLOG_ERROR,"could not parse Sun style map");
    goto err;
  }

  memset(line_buff, 0, sizeof(line_buff));

  if (s_entry->opt_list != NULL) {
    /* write the mount options to the buffer  */
    sun_opts2amd(line_buff, sizeof(line_buff), key, s_entry->opt_list);
  }

  /* Check if this is a multi-mount entry. */
  if (s_entry->mountpt_list != NULL) {
    /* multi-mount point */
    sun_multi2amd(line_buff, sizeof(line_buff), key, s_entry);
    retval = xstrdup(line_buff);
  }
  else {
    /* single mount point */
    if (s_entry->fstype != NULL) {
      if (NSTREQ(s_entry->fstype, SUN_NFS_TYPE, strlen(SUN_NFS_TYPE))) {
	/* NFS Type */
	sun_nfs2amd(line_buff, sizeof(line_buff), key, s_entry);
	retval = xstrdup(line_buff);
      }
      else if (NSTREQ(s_entry->fstype, SUN_HSFS_TYPE, strlen(SUN_HSFS_TYPE))) {
	/* HSFS Type (CD fs) */
	sun_hsfs2amd(line_buff, sizeof(line_buff), key, s_entry);
	retval = xstrdup(line_buff);
      }
      /*
       * XXX: The following fstypes are not yet supported.
       */
      else if (NSTREQ(s_entry->fstype, SUN_AUTOFS_TYPE, strlen(SUN_AUTOFS_TYPE))) {
	/* AutoFS Type */
	plog(XLOG_ERROR, "Sun fstype %s is currently not supported by Amd.",
	     s_entry->fstype);
	goto err;

      }
      else if (NSTREQ(s_entry->fstype, SUN_CACHEFS_TYPE, strlen(SUN_CACHEFS_TYPE))) {
	/* CacheFS Type */
	plog(XLOG_ERROR, "Sun fstype %s is currently not supported by Amd.",
	     s_entry->fstype);
	goto err;
      }
      else {
	plog(XLOG_ERROR, "Sun fstype %s is currently not supported by Amd.",
	     s_entry->fstype);
	goto err;
      }
    }
    else {
      plog(XLOG_INFO, "No SUN fstype specified defaulting to NFS.");
      sun_nfs2amd(line_buff, sizeof(line_buff), key, s_entry);
      retval = xstrdup(line_buff);
    }
  }

 err:
  XFREE(s_entry);
  return retval;
}