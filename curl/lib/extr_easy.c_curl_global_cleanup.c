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

/* Variables and functions */
 int /*<<< orphan*/  Curl_amiga_cleanup () ; 
 int /*<<< orphan*/  Curl_resolver_global_cleanup () ; 
 int /*<<< orphan*/  Curl_ssh_cleanup () ; 
 int /*<<< orphan*/  Curl_ssl_cleanup () ; 
 int /*<<< orphan*/  Curl_win32_cleanup (scalar_t__) ; 
 scalar_t__ init_flags ; 
 scalar_t__ initialized ; 

void curl_global_cleanup(void)
{
  if(!initialized)
    return;

  if(--initialized)
    return;

  Curl_ssl_cleanup();
  Curl_resolver_global_cleanup();

#ifdef WIN32
  Curl_win32_cleanup(init_flags);
#endif

  Curl_amiga_cleanup();

  Curl_ssh_cleanup();

  init_flags  = 0;
}