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
 scalar_t__ inferior_argc ; 
 char* inferior_args ; 
 scalar_t__ inferior_argv ; 

char *
set_inferior_args (char *newargs)
{
  char *saved_args = inferior_args;

  inferior_args = newargs;
  inferior_argc = 0;
  inferior_argv = 0;

  return saved_args;
}