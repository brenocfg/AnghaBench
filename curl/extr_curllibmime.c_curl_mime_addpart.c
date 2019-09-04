#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* nextpart; TYPE_2__* parent; } ;
typedef  TYPE_1__ curl_mimepart ;
struct TYPE_7__ {TYPE_1__* lastpart; TYPE_1__* firstpart; int /*<<< orphan*/  easy; } ;
typedef  TYPE_2__ curl_mime ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_mime_initpart (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 

curl_mimepart *curl_mime_addpart(curl_mime *mime)
{
  curl_mimepart *part;

  if(!mime)
    return NULL;

  part = (curl_mimepart *) malloc(sizeof(*part));

  if(part) {
    Curl_mime_initpart(part, mime->easy);
    part->parent = mime;

    if(mime->lastpart)
      mime->lastpart->nextpart = part;
    else
      mime->firstpart = part;

    mime->lastpart = part;
  }

  return part;
}