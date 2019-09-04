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
struct GlobalConfig {scalar_t__ libcurl; } ;
typedef  int /*<<< orphan*/  preamble ;
struct TYPE_3__ {long value; scalar_t__ name; } ;
typedef  TYPE_1__ NameValue ;
typedef  int /*<<< orphan*/  CURLoption ;
typedef  int /*<<< orphan*/  CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CODE2 (char*,char*,long) ; 
 int /*<<< orphan*/  CODE3 (char*,char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  msnprintf (char*,int,char*,char const*,...) ; 
 int /*<<< orphan*/  strlen (char*) ; 

CURLcode tool_setopt_flags(CURL *curl, struct GlobalConfig *config,
                           const char *name, CURLoption tag,
                           const NameValue *nvlist, long lval)
{
  CURLcode ret = CURLE_OK;
  bool skip = FALSE;

  ret = curl_easy_setopt(curl, tag, lval);
  if(!lval)
    skip = TRUE;

  if(config->libcurl && !skip && !ret) {
    /* we only use this for real if --libcurl was used */
    char preamble[80];          /* should accommodate any symbol name */
    long rest = lval;           /* bits not handled yet */
    const NameValue *nv = NULL;
    msnprintf(preamble, sizeof(preamble),
              "curl_easy_setopt(hnd, %s, ", name);
    for(nv = nvlist; nv->name; nv++) {
      if((nv->value & ~ rest) == 0) {
        /* all value flags contained in rest */
        rest &= ~ nv->value;    /* remove bits handled here */
        CODE3("%s(long)%s%s",
              preamble, nv->name, rest ? " |" : ");");
        if(!rest)
          break;                /* handled them all */
        /* replace with all spaces for continuation line */
        msnprintf(preamble, sizeof(preamble), "%*s", strlen(preamble), "");
      }
    }
    /* If any bits have no definition, output an explicit value.
     * This could happen if new bits are defined and used
     * but the NameValue list is not updated. */
    if(rest)
      CODE2("%s%ldL);", preamble, rest);
  }

 nomem:
  return ret;
}