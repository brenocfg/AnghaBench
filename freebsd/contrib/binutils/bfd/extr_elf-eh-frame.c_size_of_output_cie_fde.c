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
struct eh_cie_fde {int size; scalar_t__ removed; } ;

/* Variables and functions */
 unsigned int extra_augmentation_data_bytes (struct eh_cie_fde*) ; 
 unsigned int extra_augmentation_string_bytes (struct eh_cie_fde*) ; 

__attribute__((used)) static unsigned int
size_of_output_cie_fde (struct eh_cie_fde *entry, unsigned int alignment)
{
  if (entry->removed)
    return 0;
  if (entry->size == 4)
    return 4;
  return (entry->size
	  + extra_augmentation_string_bytes (entry)
	  + extra_augmentation_data_bytes (entry)
	  + alignment - 1) & -alignment;
}