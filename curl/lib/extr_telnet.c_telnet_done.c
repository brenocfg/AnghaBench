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
struct connectdata {TYPE_2__* data; } ;
struct TELNET {int /*<<< orphan*/ * telnet_vars; } ;
struct TYPE_3__ {scalar_t__ protop; } ;
struct TYPE_4__ {TYPE_1__ req; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  Curl_safefree (scalar_t__) ; 
 int /*<<< orphan*/  curl_slist_free_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static CURLcode telnet_done(struct connectdata *conn,
                                 CURLcode status, bool premature)
{
  struct TELNET *tn = (struct TELNET *)conn->data->req.protop;
  (void)status; /* unused */
  (void)premature; /* not used */

  if(!tn)
    return CURLE_OK;

  curl_slist_free_all(tn->telnet_vars);
  tn->telnet_vars = NULL;

  Curl_safefree(conn->data->req.protop);

  return CURLE_OK;
}