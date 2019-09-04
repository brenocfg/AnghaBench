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
 int DB_NMI ; 
 int DEBUGFlag ; 
 int /*<<< orphan*/  Debugger (char const*) ; 

void PE_enter_debugger(const char *cause)
{
  if (DEBUGFlag & DB_NMI)
    Debugger(cause);
}