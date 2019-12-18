#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ curl_off_t ;
struct TYPE_5__ {struct TYPE_5__* nextpart; } ;
typedef  TYPE_1__ curl_mimepart ;
struct TYPE_6__ {TYPE_1__* firstpart; int /*<<< orphan*/  boundary; } ;
typedef  TYPE_2__ curl_mime ;

/* Variables and functions */
 scalar_t__ Curl_mime_size (TYPE_1__*) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static curl_off_t multipart_size(curl_mime *mime)
{
  curl_off_t size;
  size_t boundarysize;
  curl_mimepart *part;

  if(!mime)
    return 0;           /* Not present -> empty. */

  boundarysize = 4 + strlen(mime->boundary) + 2;
  size = boundarysize;  /* Final boundary - CRLF after headers. */

  for(part = mime->firstpart; part; part = part->nextpart) {
    curl_off_t sz = Curl_mime_size(part);

    if(sz < 0)
      size = sz;

    if(size >= 0)
      size += boundarysize + sz;
  }

  return size;
}