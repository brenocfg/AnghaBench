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
struct file_data {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  brief ; 
 char** file_label ; 
 int /*<<< orphan*/  message (char*,char const*,char const*) ; 

__attribute__((used)) static int
briefly_report (int changes, struct file_data const filevec[])
{
  if (changes)
    {
      char const *label0 = file_label[0] ? file_label[0] : filevec[0].name;
      char const *label1 = file_label[1] ? file_label[1] : filevec[1].name;
      message ("Files %s and %s differ\n", label0, label1);
      if (! brief)
	changes = 2;
    }

  return changes;
}