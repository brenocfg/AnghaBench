#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* nextpart; struct TYPE_7__* firstpart; } ;
typedef  TYPE_1__ curl_mimepart ;
typedef  TYPE_1__ curl_mime ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_mime_cleanpart (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  mime_subparts_unbind (TYPE_1__*) ; 

void curl_mime_free(curl_mime *mime)
{
  curl_mimepart *part;

  if(mime) {
    mime_subparts_unbind(mime);  /* Be sure it's not referenced anymore. */
    while(mime->firstpart) {
      part = mime->firstpart;
      mime->firstpart = part->nextpart;
      Curl_mime_cleanpart(part);
      free(part);
    }
    free(mime);
  }
}