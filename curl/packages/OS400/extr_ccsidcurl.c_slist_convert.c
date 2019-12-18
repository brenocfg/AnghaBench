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
struct curl_slist {int /*<<< orphan*/  data; struct curl_slist* next; } ;

/* Variables and functions */
 struct curl_slist* Curl_slist_append_nodup (struct curl_slist*,char*) ; 
 int /*<<< orphan*/  curl_slist_free_all (struct curl_slist*) ; 
 char* dynconvert (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static struct curl_slist *
slist_convert(int dccsid, struct curl_slist *from, int sccsid)

{
  struct curl_slist *to = (struct curl_slist *) NULL;

  for(; from; from = from->next) {
    struct curl_slist *nl;
    char *cp = dynconvert(dccsid, from->data, -1, sccsid);

    if(!cp) {
      curl_slist_free_all(to);
      return (struct curl_slist *) NULL;
    }
    nl = Curl_slist_append_nodup(to, cp);
    if(!nl) {
      curl_slist_free_all(to);
      free(cp);
      return NULL;
    }
    to = nl;
  }
  return to;
}