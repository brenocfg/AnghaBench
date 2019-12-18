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
#define  STV_DEFAULT 131 
#define  STV_HIDDEN 130 
#define  STV_INTERNAL 129 
#define  STV_PROTECTED 128 
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static const char *
get_symbol_visibility (unsigned int visibility)
{
  switch (visibility)
    {
    case STV_DEFAULT:	return "DEFAULT";
    case STV_INTERNAL:	return "INTERNAL";
    case STV_HIDDEN:	return "HIDDEN";
    case STV_PROTECTED: return "PROTECTED";
    default: abort ();
    }
}