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
 scalar_t__ CURL_MASK_UINT ; 

unsigned int curlx_uztoui(size_t uznum)
{
#ifdef __INTEL_COMPILER
# pragma warning(push)
# pragma warning(disable:810) /* conversion may lose significant bits */
#endif

#if (SIZEOF_INT < SIZEOF_SIZE_T)
  DEBUGASSERT(uznum <= (size_t) CURL_MASK_UINT);
#endif
  return (unsigned int)(uznum & (size_t) CURL_MASK_UINT);

#ifdef __INTEL_COMPILER
# pragma warning(pop)
#endif
}