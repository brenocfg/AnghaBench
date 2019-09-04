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
struct IMAP {scalar_t__ transfer; } ;
struct TYPE_3__ {struct IMAP* protop; } ;
struct TYPE_4__ {TYPE_1__ req; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  Curl_setup_transfer (TYPE_2__*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FTPTRANSFER_BODY ; 

__attribute__((used)) static CURLcode imap_dophase_done(struct connectdata *conn, bool connected)
{
  struct IMAP *imap = conn->data->req.protop;

  (void)connected;

  if(imap->transfer != FTPTRANSFER_BODY)
    /* no data to transfer */
    Curl_setup_transfer(conn->data, -1, -1, FALSE, -1);

  return CURLE_OK;
}