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
 scalar_t__ curl_strequal (char*,char const*) ; 
 int /*<<< orphan*/  notef (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  warnf (int /*<<< orphan*/ ,char*) ; 

void customrequest_helper(struct OperationConfig *config, HttpReq req,
                          char *method)
{
  /* this mirrors the HttpReq enum in tool_sdecls.h */
  const char *dflt[]= {
    "GET",
    "GET",
    "HEAD",
    "POST",
    "POST"
  };

  if(!method)
    ;
  else if(curl_strequal(method, dflt[req])) {
    notef(config->global, "Unnecessary use of -X or --request, %s is already "
          "inferred.\n", dflt[req]);
  }
  else if(curl_strequal(method, "head")) {
    warnf(config->global,
          "Setting custom HTTP method to HEAD with -X/--request may not work "
          "the way you want. Consider using -I/--head instead.\n");
  }
}