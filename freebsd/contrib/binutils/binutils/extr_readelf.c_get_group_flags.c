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
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
#define  GRP_COMDAT 128 
 char* _ (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static const char *
get_group_flags (unsigned int flags)
{
  static char buff[32];
  switch (flags)
    {
    case GRP_COMDAT:
      return "COMDAT";

   default:
      snprintf (buff, sizeof (buff), _("[<unknown>: 0x%x]"), flags);
      break;
    }
  return buff;
}