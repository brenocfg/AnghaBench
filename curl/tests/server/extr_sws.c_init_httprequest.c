#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct httprequest {scalar_t__ upgrade_request; scalar_t__ upgrade; scalar_t__ done_processing; scalar_t__ connect_port; scalar_t__ callcount; scalar_t__ prot_version; int /*<<< orphan*/  rcmd; scalar_t__ writedelay; scalar_t__ skip; void* ntlm; void* digest; scalar_t__ cl; void* auth; void* auth_req; int /*<<< orphan*/  open; void* connect_request; scalar_t__ partno; int /*<<< orphan*/  testno; scalar_t__ offset; scalar_t__ checkindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOCNUMBER_NOTHING ; 
 void* FALSE ; 
 int /*<<< orphan*/  RCMD_NORMALREQ ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void init_httprequest(struct httprequest *req)
{
  req->checkindex = 0;
  req->offset = 0;
  req->testno = DOCNUMBER_NOTHING;
  req->partno = 0;
  req->connect_request = FALSE;
  req->open = TRUE;
  req->auth_req = FALSE;
  req->auth = FALSE;
  req->cl = 0;
  req->digest = FALSE;
  req->ntlm = FALSE;
  req->skip = 0;
  req->writedelay = 0;
  req->rcmd = RCMD_NORMALREQ;
  req->prot_version = 0;
  req->callcount = 0;
  req->connect_port = 0;
  req->done_processing = 0;
  req->upgrade = 0;
  req->upgrade_request = 0;
}