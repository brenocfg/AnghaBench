#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t offset; } ;
struct TYPE_4__ {TYPE_1__ state; int /*<<< orphan*/ * data; scalar_t__ datasize; } ;
typedef  TYPE_2__ curl_mimepart ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 

__attribute__((used)) static size_t mime_mem_read(char *buffer, size_t size, size_t nitems,
                            void *instream)
{
  curl_mimepart *part = (curl_mimepart *) instream;
  size_t sz = (size_t) part->datasize - part->state.offset;
  (void) size;   /* Always 1.*/

  if(sz > nitems)
    sz = nitems;

  if(sz)
    memcpy(buffer, (char *) &part->data[part->state.offset], sz);

  part->state.offset += sz;
  return sz;
}