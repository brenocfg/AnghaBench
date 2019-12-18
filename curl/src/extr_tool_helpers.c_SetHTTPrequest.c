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
struct OperationConfig {int /*<<< orphan*/  global; } ;
typedef  size_t HttpReq ;

/* Variables and functions */
 size_t HTTPREQ_UNSPEC ; 
 int /*<<< orphan*/  warnf (int /*<<< orphan*/ ,char*,char const*,char const*) ; 

int SetHTTPrequest(struct OperationConfig *config, HttpReq req, HttpReq *store)
{
  /* this mirrors the HttpReq enum in tool_sdecls.h */
  const char *reqname[]= {
    "", /* unspec */
    "GET (-G, --get)",
    "HEAD (-I, --head)",
    "multipart formpost (-F, --form)",
    "POST (-d, --data)"
  };

  if((*store == HTTPREQ_UNSPEC) ||
     (*store == req)) {
    *store = req;
    return 0;
  }
  warnf(config->global, "You can only select one HTTP request method! "
        "You asked for both %s and %s.\n",
        reqname[req], reqname[*store]);

  return 1;
}