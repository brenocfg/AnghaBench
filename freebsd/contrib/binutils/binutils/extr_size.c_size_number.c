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
typedef  scalar_t__ bfd_size_type ;

/* Variables and functions */
 scalar_t__ decimal ; 
 scalar_t__ octal ; 
 scalar_t__ radix ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
size_number (bfd_size_type num)
{
  char buffer[40];

  sprintf (buffer,
	   (radix == decimal ? "%lu" :
	   ((radix == octal) ? "0%lo" : "0x%lx")),
	   (unsigned long) num);

  return strlen (buffer);
}