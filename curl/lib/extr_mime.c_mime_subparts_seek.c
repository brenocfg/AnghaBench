#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ curl_off_t ;
struct TYPE_5__ {struct TYPE_5__* nextpart; } ;
typedef  TYPE_1__ curl_mimepart ;
struct TYPE_7__ {scalar_t__ state; } ;
struct TYPE_6__ {TYPE_3__ state; TYPE_1__* firstpart; } ;
typedef  TYPE_2__ curl_mime ;

/* Variables and functions */
 int CURL_SEEKFUNC_CANTSEEK ; 
 int CURL_SEEKFUNC_OK ; 
 scalar_t__ MIMESTATE_BEGIN ; 
 int SEEK_SET ; 
 int mime_part_rewind (TYPE_1__*) ; 
 int /*<<< orphan*/  mimesetstate (TYPE_3__*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mime_subparts_seek(void *instream, curl_off_t offset, int whence)
{
  curl_mime *mime = (curl_mime *) instream;
  curl_mimepart *part;
  int result = CURL_SEEKFUNC_OK;

  if(whence != SEEK_SET || offset)
    return CURL_SEEKFUNC_CANTSEEK;    /* Only support full rewind. */

  if(mime->state.state == MIMESTATE_BEGIN)
   return CURL_SEEKFUNC_OK;           /* Already rewound. */

  for(part = mime->firstpart; part; part = part->nextpart) {
    int res = mime_part_rewind(part);
    if(res != CURL_SEEKFUNC_OK)
      result = res;
  }

  if(result == CURL_SEEKFUNC_OK)
    mimesetstate(&mime->state, MIMESTATE_BEGIN, NULL);

  return result;
}