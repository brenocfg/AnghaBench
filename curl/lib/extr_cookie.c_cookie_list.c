#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct curl_slist {int dummy; } ;
struct Curl_easy {TYPE_1__* cookies; } ;
struct Cookie {int /*<<< orphan*/  domain; struct Cookie* next; } ;
struct TYPE_2__ {scalar_t__ numcookies; struct Cookie** cookies; } ;

/* Variables and functions */
 unsigned int COOKIE_HASH_SIZE ; 
 struct curl_slist* Curl_slist_append_nodup (struct curl_slist*,char*) ; 
 int /*<<< orphan*/  curl_slist_free_all (struct curl_slist*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_netscape_format (struct Cookie*) ; 

__attribute__((used)) static struct curl_slist *cookie_list(struct Curl_easy *data)
{
  struct curl_slist *list = NULL;
  struct curl_slist *beg;
  struct Cookie *c;
  char *line;
  unsigned int i;

  if((data->cookies == NULL) ||
      (data->cookies->numcookies == 0))
    return NULL;

  for(i = 0; i < COOKIE_HASH_SIZE; i++) {
    for(c = data->cookies->cookies[i]; c; c = c->next) {
      if(!c->domain)
        continue;
      line = get_netscape_format(c);
      if(!line) {
        curl_slist_free_all(list);
        return NULL;
      }
      beg = Curl_slist_append_nodup(list, line);
      if(!beg) {
        free(line);
        curl_slist_free_all(list);
        return NULL;
      }
      list = beg;
    }
  }

  return list;
}