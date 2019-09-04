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
 int /*<<< orphan*/  Curl_ssl_cleanup () ; 
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

#if defined(USE_LIBSSH2) && defined(HAVE_LIBSSH2_EXIT)
  (void)libssh2_exit();
#endif

#if defined(USE_LIBSSH)
  (void)ssh_finalize();
#endif

  init_flags  = 0;
}