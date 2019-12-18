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
 int /*<<< orphan*/  CLK_CXX98 ; 
 int /*<<< orphan*/  CLK_GNUCXX ; 
 int /*<<< orphan*/  cpp_set_lang (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int flag_iso ; 
 int flag_no_gnu_keywords ; 
 int flag_no_nonansi_builtin ; 
 int /*<<< orphan*/  parse_in ; 

__attribute__((used)) static void
set_std_cxx98 (int iso)
{
  cpp_set_lang (parse_in, iso ? CLK_CXX98: CLK_GNUCXX);
  flag_no_gnu_keywords = iso;
  flag_no_nonansi_builtin = iso;
  flag_iso = iso;
}