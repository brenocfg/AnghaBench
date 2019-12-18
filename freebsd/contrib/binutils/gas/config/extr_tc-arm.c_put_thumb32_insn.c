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
 int THUMB_SIZE ; 
 int /*<<< orphan*/  md_number_to_chars (char*,unsigned long,int) ; 

__attribute__((used)) static void
put_thumb32_insn (char * buf, unsigned long insn)
{
  md_number_to_chars (buf, insn >> 16, THUMB_SIZE);
  md_number_to_chars (buf + THUMB_SIZE, insn, THUMB_SIZE);
}