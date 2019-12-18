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
typedef  unsigned int hashval_t ;

/* Variables and functions */
 unsigned int CHAR_BIT ; 

__attribute__((used)) static hashval_t
def_hash (const void *def)
{
  unsigned result, i;
  const char *string = *(const char *const *) def;

  for (result = i = 0; *string++ != '\0'; i++)
    result += ((unsigned char) *string << (i % CHAR_BIT));
  return result;
}