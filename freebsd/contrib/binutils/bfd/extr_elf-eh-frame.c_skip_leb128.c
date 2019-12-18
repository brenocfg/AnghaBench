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
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  read_byte (int /*<<< orphan*/ **,int /*<<< orphan*/ *,unsigned char*) ; 

__attribute__((used)) static bfd_boolean
skip_leb128 (bfd_byte **iter, bfd_byte *end)
{
  unsigned char byte;
  do
    if (!read_byte (iter, end, &byte))
      return FALSE;
  while (byte & 0x80);
  return TRUE;
}