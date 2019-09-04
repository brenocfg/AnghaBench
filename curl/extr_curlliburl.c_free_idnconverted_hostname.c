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
struct hostname {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void free_idnconverted_hostname(struct hostname *host)
{
#if defined(USE_LIBIDN2)
  if(host->encalloc) {
    idn2_free(host->encalloc); /* must be freed with idn2_free() since this was
                                 allocated by libidn */
    host->encalloc = NULL;
  }
#elif defined(USE_WIN32_IDN)
  free(host->encalloc); /* must be freed with free() since this was
                           allocated by curl_win32_idn_to_ascii */
  host->encalloc = NULL;
#else
  (void)host;
#endif
}