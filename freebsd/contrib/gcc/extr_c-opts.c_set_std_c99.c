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
 int /*<<< orphan*/  CLK_GNUC99 ; 
 int /*<<< orphan*/  CLK_STDC99 ; 
 int /*<<< orphan*/  cpp_set_lang (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int flag_iso ; 
 int flag_isoc94 ; 
 int flag_isoc99 ; 
 int flag_no_asm ; 
 int flag_no_nonansi_builtin ; 
 int /*<<< orphan*/  parse_in ; 

__attribute__((used)) static void
set_std_c99 (int iso)
{
  cpp_set_lang (parse_in, iso ? CLK_STDC99: CLK_GNUC99);
  flag_no_asm = iso;
  flag_no_nonansi_builtin = iso;
  flag_iso = iso;
  flag_isoc99 = 1;
  flag_isoc94 = 1;
}