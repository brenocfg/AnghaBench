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
 int CURLFTPSSL_CCC_ACTIVE ; 
 int CURLFTPSSL_CCC_PASSIVE ; 
 scalar_t__ curl_strequal (char*,char const*) ; 
 int /*<<< orphan*/  warnf (int /*<<< orphan*/ ,char*,char const*) ; 

int ftpcccmethod(struct OperationConfig *config, const char *str)
{
  if(curl_strequal("passive", str))
    return CURLFTPSSL_CCC_PASSIVE;
  if(curl_strequal("active", str))
    return CURLFTPSSL_CCC_ACTIVE;

  warnf(config->global, "unrecognized ftp CCC method '%s', using default\n",
        str);

  return CURLFTPSSL_CCC_PASSIVE;
}