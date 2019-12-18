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
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ CURL_MASK_SINT ; 
 int /*<<< orphan*/  DEBUGASSERT (int) ; 

int curlx_sztosi(ssize_t sznum)
{
#ifdef __INTEL_COMPILER
#  pragma warning(push)
#  pragma warning(disable:810) /* conversion may lose significant bits */
#endif

  DEBUGASSERT(sznum >= 0);
#if (SIZEOF_INT < SIZEOF_SIZE_T)
  DEBUGASSERT((size_t) sznum <= (size_t) CURL_MASK_SINT);
#endif
  return (int)(sznum & (ssize_t) CURL_MASK_SINT);

#ifdef __INTEL_COMPILER
#  pragma warning(pop)
#endif
}