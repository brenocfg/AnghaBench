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
 int DEFAULT_INIT_PRIORITY ; 
 int atoi (char const*) ; 

__attribute__((used)) static int
extract_init_priority (const char *name)
{
  int pos = 0, pri;

  while (name[pos] == '_')
    ++pos;
  pos += 10; /* strlen ("GLOBAL__X_") */

  /* Extract init_p number from ctor/dtor name.  */
  pri = atoi (name + pos);
  return pri ? pri : DEFAULT_INIT_PRIORITY;
}