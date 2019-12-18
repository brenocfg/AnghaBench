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
typedef  scalar_t__ curl_strdup_callback ;
typedef  scalar_t__ curl_realloc_callback ;
typedef  scalar_t__ curl_malloc_callback ;
typedef  scalar_t__ curl_free_callback ;
typedef  scalar_t__ curl_calloc_callback ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_FAILED_INIT ; 
 int /*<<< orphan*/  CURLE_OK ; 
 scalar_t__ Curl_ccalloc ; 
 scalar_t__ Curl_cfree ; 
 scalar_t__ Curl_cmalloc ; 
 scalar_t__ Curl_crealloc ; 
 scalar_t__ Curl_cstrdup ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  global_init (long,int /*<<< orphan*/ ) ; 
 scalar_t__ initialized ; 

CURLcode curl_global_init_mem(long flags, curl_malloc_callback m,
                              curl_free_callback f, curl_realloc_callback r,
                              curl_strdup_callback s, curl_calloc_callback c)
{
  /* Invalid input, return immediately */
  if(!m || !f || !r || !s || !c)
    return CURLE_FAILED_INIT;

  if(initialized) {
    /* Already initialized, don't do it again, but bump the variable anyway to
       work like curl_global_init() and require the same amount of cleanup
       calls. */
    initialized++;
    return CURLE_OK;
  }

  /* set memory functions before global_init() in case it wants memory
     functions */
  Curl_cmalloc = m;
  Curl_cfree = f;
  Curl_cstrdup = s;
  Curl_crealloc = r;
  Curl_ccalloc = c;

  /* Call the actual init function, but without setting */
  return global_init(flags, FALSE);
}