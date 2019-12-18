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
struct attribute {scalar_t__ form; } ;

/* Variables and functions */
 scalar_t__ DW_FORM_block ; 
 scalar_t__ DW_FORM_block1 ; 
 scalar_t__ DW_FORM_block2 ; 
 scalar_t__ DW_FORM_block4 ; 

__attribute__((used)) static int
attr_form_is_block (struct attribute *attr)
{
  return (attr == NULL ? 0 :
      attr->form == DW_FORM_block1
      || attr->form == DW_FORM_block2
      || attr->form == DW_FORM_block4
      || attr->form == DW_FORM_block);
}