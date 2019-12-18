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
struct ieee_handle {int dummy; } ;
typedef  unsigned int bfd_vma ;
typedef  int bfd_boolean ;

/* Variables and functions */
 scalar_t__ ieee_asn_record_enum ; 
 scalar_t__ ieee_write_2bytes (struct ieee_handle*,int) ; 
 scalar_t__ ieee_write_number (struct ieee_handle*,unsigned int) ; 

__attribute__((used)) static bfd_boolean
ieee_write_asn (struct ieee_handle *info, unsigned int indx, bfd_vma val)
{
  return (ieee_write_2bytes (info, (int) ieee_asn_record_enum)
	  && ieee_write_number (info, indx)
	  && ieee_write_number (info, val));
}