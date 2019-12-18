#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  headers; int /*<<< orphan*/  data; int /*<<< orphan*/  encoder; int /*<<< orphan*/  type; int /*<<< orphan*/  filename; int /*<<< orphan*/  name; struct TYPE_4__* prev; struct TYPE_4__* subparts; } ;
typedef  TYPE_1__ tool_mime ;

/* Variables and functions */
 int /*<<< orphan*/  CONST_SAFEFREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_slist_free_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void tool_mime_free(tool_mime *mime)
{
  if(mime) {
    if(mime->subparts)
      tool_mime_free(mime->subparts);
    if(mime->prev)
      tool_mime_free(mime->prev);
    CONST_SAFEFREE(mime->name);
    CONST_SAFEFREE(mime->filename);
    CONST_SAFEFREE(mime->type);
    CONST_SAFEFREE(mime->encoder);
    CONST_SAFEFREE(mime->data);
    curl_slist_free_all(mime->headers);
    free(mime);
  }
}