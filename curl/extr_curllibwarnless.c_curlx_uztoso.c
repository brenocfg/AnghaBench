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
typedef  int /*<<< orphan*/  curl_off_t ;

/* Variables and functions */
 scalar_t__ CURL_MASK_SCOFFT ; 
 int /*<<< orphan*/  DEBUGASSERT (int) ; 

curl_off_t curlx_uztoso(size_t uznum)
{
#ifdef __INTEL_COMPILER
#  pragma warning(push)
#  pragma warning(disable:810) /* conversion may lose significant bits */
#elif defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable:4310) /* cast truncates constant value */
#endif

  DEBUGASSERT(uznum <= (size_t) CURL_MASK_SCOFFT);
  return (curl_off_t)(uznum & (size_t) CURL_MASK_SCOFFT);

#if defined(__INTEL_COMPILER) || defined(_MSC_VER)
#  pragma warning(pop)
#endif
}