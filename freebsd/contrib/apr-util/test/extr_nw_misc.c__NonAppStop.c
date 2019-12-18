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
 int /*<<< orphan*/  getcharacter () ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 

void _NonAppStop( void )
{
  if (getenv("_IN_NETWARE_BASH_") == NULL) {
    printf("\r\n<Press any key to close screen> ");
    getcharacter();
  }
}