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
 int SYSTEM_PRINT ; 
 int /*<<< orphan*/  strcpy (char const*,char const*) ; 
 char const* systemChat ; 
 char const* teamChat1 ; 
 char const* teamChat2 ; 

void CG_SetPrintString(int type, const char *p) {
  if (type == SYSTEM_PRINT) {
    strcpy(systemChat, p);
  } else {
    strcpy(teamChat2, teamChat1);
    strcpy(teamChat1, p);
  }
}