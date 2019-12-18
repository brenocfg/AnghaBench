#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thumb_noop ;
struct TYPE_5__ {scalar_t__ fr_type; int fr_address; int fr_fix; char* fr_literal; int fr_var; scalar_t__ tc_frag_data; TYPE_1__* fr_next; } ;
typedef  TYPE_2__ fragS ;
typedef  int /*<<< orphan*/  arm_noop ;
struct TYPE_4__ {int fr_address; } ;

/* Variables and functions */
 int MAX_MEM_FOR_RS_ALIGN_CODE ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rs_align_code ; 
 scalar_t__ target_big_endian ; 

void
arm_handle_align (fragS * fragP)
{
  static char const arm_noop[4] = { 0x00, 0x00, 0xa0, 0xe1 };
  static char const thumb_noop[2] = { 0xc0, 0x46 };
  static char const arm_bigend_noop[4] = { 0xe1, 0xa0, 0x00, 0x00 };
  static char const thumb_bigend_noop[2] = { 0x46, 0xc0 };

  int bytes, fix, noop_size;
  char * p;
  const char * noop;

  if (fragP->fr_type != rs_align_code)
    return;

  bytes = fragP->fr_next->fr_address - fragP->fr_address - fragP->fr_fix;
  p = fragP->fr_literal + fragP->fr_fix;
  fix = 0;

  if (bytes > MAX_MEM_FOR_RS_ALIGN_CODE)
    bytes &= MAX_MEM_FOR_RS_ALIGN_CODE;

  if (fragP->tc_frag_data)
    {
      if (target_big_endian)
	noop = thumb_bigend_noop;
      else
	noop = thumb_noop;
      noop_size = sizeof (thumb_noop);
    }
  else
    {
      if (target_big_endian)
	noop = arm_bigend_noop;
      else
	noop = arm_noop;
      noop_size = sizeof (arm_noop);
    }

  if (bytes & (noop_size - 1))
    {
      fix = bytes & (noop_size - 1);
      memset (p, 0, fix);
      p += fix;
      bytes -= fix;
    }

  while (bytes >= noop_size)
    {
      memcpy (p, noop, noop_size);
      p += noop_size;
      bytes -= noop_size;
      fix += noop_size;
    }

  fragP->fr_fix += fix;
  fragP->fr_var = noop_size;
}