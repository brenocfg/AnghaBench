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
 scalar_t__ CURL_MASK_UCHAR ; 
 int /*<<< orphan*/  DEBUGASSERT (int) ; 

unsigned char curlx_ultouc(unsigned long ulnum)
{
#ifdef __INTEL_COMPILER
#  pragma warning(push)
#  pragma warning(disable:810) /* conversion may lose significant bits */
#endif

  DEBUGASSERT(ulnum <= (unsigned long) CURL_MASK_UCHAR);
  return (unsigned char)(ulnum & (unsigned long) CURL_MASK_UCHAR);

#ifdef __INTEL_COMPILER
#  pragma warning(pop)
#endif
}