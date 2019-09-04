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

/* Variables and functions */
 long CURLGSSAPI_DELEGATION_FLAG ; 
 long CURLGSSAPI_DELEGATION_NONE ; 
 long CURLGSSAPI_DELEGATION_POLICY_FLAG ; 
 scalar_t__ curl_strequal (char*,char*) ; 
 int /*<<< orphan*/  warnf (int /*<<< orphan*/ ,char*,char*) ; 

long delegation(struct OperationConfig *config, char *str)
{
  if(curl_strequal("none", str))
    return CURLGSSAPI_DELEGATION_NONE;
  if(curl_strequal("policy", str))
    return CURLGSSAPI_DELEGATION_POLICY_FLAG;
  if(curl_strequal("always", str))
    return CURLGSSAPI_DELEGATION_FLAG;

  warnf(config->global, "unrecognized delegation method '%s', using none\n",
        str);

  return CURLGSSAPI_DELEGATION_NONE;
}