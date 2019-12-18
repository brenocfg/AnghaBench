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
struct curl_httppost {int flags; struct curl_httppost* showfilename; struct curl_httppost* contenttype; struct curl_httppost* contents; struct curl_httppost* name; struct curl_httppost* more; struct curl_httppost* next; } ;

/* Variables and functions */
 int HTTPPOST_BUFFER ; 
 int HTTPPOST_CALLBACK ; 
 int HTTPPOST_PTRCONTENTS ; 
 int HTTPPOST_PTRNAME ; 
 int /*<<< orphan*/  free (struct curl_httppost*) ; 

void curl_formfree(struct curl_httppost *form)
{
  struct curl_httppost *next;

  if(!form)
    /* no form to free, just get out of this */
    return;

  do {
    next = form->next;  /* the following form line */

    /* recurse to sub-contents */
    curl_formfree(form->more);

    if(!(form->flags & HTTPPOST_PTRNAME))
      free(form->name); /* free the name */
    if(!(form->flags &
         (HTTPPOST_PTRCONTENTS|HTTPPOST_BUFFER|HTTPPOST_CALLBACK))
      )
      free(form->contents); /* free the contents */
    free(form->contenttype); /* free the content type */
    free(form->showfilename); /* free the faked file name */
    free(form);       /* free the struct */
    form = next;
  } while(form); /* continue */
}