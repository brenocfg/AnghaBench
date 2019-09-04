#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t bufend; size_t bufbeg; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ mime_encoder_state ;
struct TYPE_5__ {TYPE_1__ encstate; } ;
typedef  TYPE_2__ curl_mimepart ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static size_t encoder_nop_read(char *buffer, size_t size, bool ateof,
                               curl_mimepart *part)
{
  mime_encoder_state *st = &part->encstate;
  size_t insize = st->bufend - st->bufbeg;

  (void) ateof;

  if(size > insize)
    size = insize;
  if(size)
    memcpy(buffer, st->buf, size);
  st->bufbeg += size;
  return size;
}