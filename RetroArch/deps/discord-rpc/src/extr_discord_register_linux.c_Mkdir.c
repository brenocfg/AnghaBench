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
 scalar_t__ EEXIST ; 
 scalar_t__ errno ; 
 int mkdir (char const*,int) ; 

__attribute__((used)) static bool Mkdir(const char* path)
{
   int result = mkdir(path, 0755);
   if (result == 0)
      return true;
   if (errno == EEXIST)
      return true;
   return false;
}