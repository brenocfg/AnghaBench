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
typedef  int /*<<< orphan*/  XML_Char ;

/* Variables and functions */
 int /*<<< orphan*/  NSSEP ; 
 int tcscmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ tcsrchr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nsattcmp(const void *p1, const void *p2)
{
  const XML_Char *att1 = *(const XML_Char **)p1;
  const XML_Char *att2 = *(const XML_Char **)p2;
  int sep1 = (tcsrchr(att1, NSSEP) != 0);
  int sep2 = (tcsrchr(att1, NSSEP) != 0);
  if (sep1 != sep2)
    return sep1 - sep2;
  return tcscmp(att1, att2);
}