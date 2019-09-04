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
 scalar_t__ CURL_MASK_USHORT ; 
 int /*<<< orphan*/  DEBUGASSERT (int) ; 

unsigned short curlx_uitous(unsigned int uinum)
{
#ifdef __INTEL_COMPILER
#  pragma warning(push)
#  pragma warning(disable:810) /* conversion may lose significant bits */
#endif

  DEBUGASSERT(uinum <= (unsigned int) CURL_MASK_USHORT);
  return (unsigned short) (uinum & (unsigned int) CURL_MASK_USHORT);

#ifdef __INTEL_COMPILER
#  pragma warning(pop)
#endif
}