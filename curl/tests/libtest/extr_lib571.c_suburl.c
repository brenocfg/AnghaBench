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
 char* curl_maprintf (char*,char const*,int) ; 

__attribute__((used)) static char *suburl(const char *base, int i)
{
  return curl_maprintf("%s%.4d", base, i);
}