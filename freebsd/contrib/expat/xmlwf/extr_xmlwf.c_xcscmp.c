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
typedef  scalar_t__ XML_Char ;

/* Variables and functions */

__attribute__((used)) static int xcscmp(const XML_Char *xs, const XML_Char *xt)
{
  while (*xs != 0 && *xt != 0) {
    if (*xs < *xt)
      return -1;
    if (*xs > *xt)
      return 1;
    xs++;
    xt++;
  }
  if (*xs < *xt)
    return -1;
  if (*xs > *xt)
    return 1;
  return 0;
}