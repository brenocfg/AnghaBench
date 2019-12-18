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
typedef  int /*<<< orphan*/  dwarf_vma ;

/* Variables and functions */
 int DW_EH_PE_signed ; 
 int /*<<< orphan*/  byte_get (unsigned char*,int) ; 
 int /*<<< orphan*/  byte_get_signed (unsigned char*,int) ; 
 int size_of_encoded_value (int) ; 

__attribute__((used)) static dwarf_vma
get_encoded_value (unsigned char *data, int encoding)
{
  int size = size_of_encoded_value (encoding);

  if (encoding & DW_EH_PE_signed)
    return byte_get_signed (data, size);
  else
    return byte_get (data, size);
}