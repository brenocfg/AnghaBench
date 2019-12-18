#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct connectdata {TYPE_3__* data; } ;
struct TYPE_8__ {scalar_t__ postsize; size_t postdata; int /*<<< orphan*/  fread_in; int /*<<< orphan*/  fread_func; } ;
struct HTTP {scalar_t__ postsize; scalar_t__ sending; size_t postdata; TYPE_4__ backup; } ;
typedef  scalar_t__ curl_off_t ;
struct TYPE_6__ {int /*<<< orphan*/  in; int /*<<< orphan*/  fread_func; } ;
struct TYPE_5__ {int /*<<< orphan*/  forbidchunk; struct HTTP* protop; } ;
struct TYPE_7__ {TYPE_2__ state; TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HTTPSEND_REQUEST ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (char*,size_t,size_t) ; 

__attribute__((used)) static size_t readmoredata(char *buffer,
                           size_t size,
                           size_t nitems,
                           void *userp)
{
  struct connectdata *conn = (struct connectdata *)userp;
  struct HTTP *http = conn->data->req.protop;
  size_t fullsize = size * nitems;

  if(!http->postsize)
    /* nothing to return */
    return 0;

  /* make sure that a HTTP request is never sent away chunked! */
  conn->data->req.forbidchunk = (http->sending == HTTPSEND_REQUEST)?TRUE:FALSE;

  if(http->postsize <= (curl_off_t)fullsize) {
    memcpy(buffer, http->postdata, (size_t)http->postsize);
    fullsize = (size_t)http->postsize;

    if(http->backup.postsize) {
      /* move backup data into focus and continue on that */
      http->postdata = http->backup.postdata;
      http->postsize = http->backup.postsize;
      conn->data->state.fread_func = http->backup.fread_func;
      conn->data->state.in = http->backup.fread_in;

      http->sending++; /* move one step up */

      http->backup.postsize = 0;
    }
    else
      http->postsize = 0;

    return fullsize;
  }

  memcpy(buffer, http->postdata, fullsize);
  http->postdata += fullsize;
  http->postsize -= fullsize;

  return fullsize;
}