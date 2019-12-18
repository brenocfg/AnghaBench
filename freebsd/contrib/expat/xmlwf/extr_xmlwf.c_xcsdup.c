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
 scalar_t__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__ const*,int) ; 

__attribute__((used)) static XML_Char *xcsdup(const XML_Char *s)
{
  XML_Char *result;
  int count = 0;
  int numBytes;

  /* Get the length of the string, including terminator */
  while (s[count++] != 0) {
    /* Do nothing */
  }
  numBytes = count * sizeof(XML_Char);
  result = malloc(numBytes);
  if (result == NULL)
    return NULL;
  memcpy(result, s, numBytes);
  return result;
}