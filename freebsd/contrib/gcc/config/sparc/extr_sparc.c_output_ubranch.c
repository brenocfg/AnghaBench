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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int INSN_ADDRESSES (int /*<<< orphan*/ ) ; 
 scalar_t__ INSN_ADDRESSES_SET_P () ; 
 int /*<<< orphan*/  INSN_UID (int /*<<< orphan*/ ) ; 
 scalar_t__ TARGET_V9 ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

const char *
output_ubranch (rtx dest, int label, rtx insn)
{
  static char string[64];
  bool v9_form = false;
  char *p;

  if (TARGET_V9 && INSN_ADDRESSES_SET_P ())
    {
      int delta = (INSN_ADDRESSES (INSN_UID (dest))
		   - INSN_ADDRESSES (INSN_UID (insn)));
      /* Leave some instructions for "slop".  */
      if (delta >= -260000 && delta < 260000)
	v9_form = true;
    }

  if (v9_form)
    strcpy (string, "ba%*,pt\t%%xcc, ");
  else
    strcpy (string, "b%*\t");

  p = strchr (string, '\0');
  *p++ = '%';
  *p++ = 'l';
  *p++ = '0' + label;
  *p++ = '%';
  *p++ = '(';
  *p = '\0';

  return string;
}