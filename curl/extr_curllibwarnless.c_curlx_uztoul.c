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
 scalar_t__ CURL_MASK_ULONG ; 

unsigned long curlx_uztoul(size_t uznum)
{
#ifdef __INTEL_COMPILER
# pragma warning(push)
# pragma warning(disable:810) /* conversion may lose significant bits */
#endif

#if (SIZEOF_LONG < SIZEOF_SIZE_T)
  DEBUGASSERT(uznum <= (size_t) CURL_MASK_ULONG);
#endif
  return (unsigned long)(uznum & (size_t) CURL_MASK_ULONG);

#ifdef __INTEL_COMPILER
# pragma warning(pop)
#endif
}