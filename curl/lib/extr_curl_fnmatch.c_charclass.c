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
typedef  int /*<<< orphan*/  char_class ;

/* Variables and functions */
 int /*<<< orphan*/  CCLASS_DIGIT ; 
 int /*<<< orphan*/  CCLASS_LOWER ; 
 int /*<<< orphan*/  CCLASS_OTHER ; 
 int /*<<< orphan*/  CCLASS_UPPER ; 
 scalar_t__ ISDIGIT (unsigned char) ; 
 scalar_t__ ISLOWER (unsigned char) ; 
 scalar_t__ ISUPPER (unsigned char) ; 

__attribute__((used)) static char_class charclass(unsigned char c)
{
  if(ISUPPER(c))
    return CCLASS_UPPER;
  if(ISLOWER(c))
    return CCLASS_LOWER;
  if(ISDIGIT(c))
    return CCLASS_DIGIT;
  return CCLASS_OTHER;
}