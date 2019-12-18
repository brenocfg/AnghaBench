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
typedef  int /*<<< orphan*/  var ;

/* Variables and functions */
 int /*<<< orphan*/  $ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  File ; 
 int scan_from (int /*<<< orphan*/ ,int,char*) ; 
 int scan_from_with (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 

int scanln_with(const char* fmt, var args) {
  int pos = 0;
  pos = scan_from_with($(File, stdin), pos, fmt, args);
  pos = scan_from($(File, stdin), pos, "\n");
  return pos;
}