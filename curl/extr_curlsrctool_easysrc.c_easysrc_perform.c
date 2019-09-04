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
struct curl_slist {char* data; struct curl_slist* next; } ;
struct TYPE_3__ {struct curl_slist* first; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CHKRET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  easysrc_add (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  easysrc_code ; 
 TYPE_1__* easysrc_toohard ; 
 int /*<<< orphan*/  slist_wc_free_all (TYPE_1__*) ; 
 char** srchard ; 

CURLcode easysrc_perform(void)
{
  /* Note any setopt calls which we could not convert */
  if(easysrc_toohard) {
    int i;
    struct curl_slist *ptr;
    const char *c;
    CHKRET(easysrc_add(&easysrc_code, ""));
    /* Preamble comment */
    for(i = 0; ((c = srchard[i]) != NULL); i++)
      CHKRET(easysrc_add(&easysrc_code, c));
    /* Each unconverted option */
    if(easysrc_toohard) {
      for(ptr = easysrc_toohard->first; ptr; ptr = ptr->next)
        CHKRET(easysrc_add(&easysrc_code, ptr->data));
    }
    CHKRET(easysrc_add(&easysrc_code, ""));
    CHKRET(easysrc_add(&easysrc_code, "*/"));

    slist_wc_free_all(easysrc_toohard);
    easysrc_toohard = NULL;
  }

  CHKRET(easysrc_add(&easysrc_code, ""));
  CHKRET(easysrc_add(&easysrc_code, "ret = curl_easy_perform(hnd);"));
  CHKRET(easysrc_add(&easysrc_code, ""));

  return CURLE_OK;
}