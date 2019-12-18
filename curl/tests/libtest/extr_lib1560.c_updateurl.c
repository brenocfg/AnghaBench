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
typedef  int /*<<< orphan*/  CURLUcode ;
typedef  scalar_t__ CURLUPart ;
typedef  int /*<<< orphan*/  CURLU ;

/* Variables and functions */
 int /*<<< orphan*/  CURLUE_OK ; 
 scalar_t__ CURLUPART_ZONEID ; 
 int /*<<< orphan*/  curl_url_set (int /*<<< orphan*/ *,scalar_t__,char*,unsigned int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 scalar_t__ part2id (char*) ; 
 int sscanf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static CURLUcode updateurl(CURLU *u, const char *cmd, unsigned int setflags)
{
  const char *p = cmd;
  CURLUcode uc;

  /* make sure the last command ends with a comma too! */
  while(p) {
    char *e = strchr(p, ',');
    if(e) {
      size_t n = e-p;
      char buf[80];
      char part[80];
      char value[80];
      memcpy(buf, p, n);
      buf[n] = 0;
      if(2 == sscanf(buf, "%79[^=]=%79[^,]", part, value)) {
        CURLUPart what = part2id(part);
#if 0
        /* for debugging this */
        fprintf(stderr, "%s = %s [%d]\n", part, value, (int)what);
#endif
        if(what > CURLUPART_ZONEID)
          fprintf(stderr, "UNKNOWN part '%s'\n", part);

        if(!strcmp("NULL", value))
          uc = curl_url_set(u, what, NULL, setflags);
        else if(!strcmp("\"\"", value))
          uc = curl_url_set(u, what, "", setflags);
        else
          uc = curl_url_set(u, what, value, setflags);
        if(uc)
          return uc;
      }
      p = e + 1;
      continue;
    }
    break;
  }
  return CURLUE_OK;
}