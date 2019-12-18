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
#define  STO_MIPS16 129 
#define  STO_OPTIONAL 128 

__attribute__((used)) static const char *
get_mips_symbol_other (unsigned int other)
{
  switch (other)
    {
    case STO_OPTIONAL:  return "OPTIONAL";
    case STO_MIPS16:    return "MIPS16";
    default:      	return NULL;
    }
}