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
 unsigned long S_IRGRP ; 
 unsigned long S_IROTH ; 
 unsigned long S_IRUSR ; 
 unsigned long S_IWGRP ; 
 unsigned long S_IWOTH ; 
 unsigned long S_IWUSR ; 
 unsigned long S_IXGRP ; 
 unsigned long S_IXOTH ; 
 unsigned long S_IXUSR ; 
 char ftypelet (unsigned long) ; 
 int /*<<< orphan*/  setst (unsigned long,char*) ; 

void
mode_string (unsigned long mode, char *str)
{
  str[0] = ftypelet ((unsigned long) mode);
  str[1] = (mode & S_IRUSR) != 0 ? 'r' : '-';
  str[2] = (mode & S_IWUSR) != 0 ? 'w' : '-';
  str[3] = (mode & S_IXUSR) != 0 ? 'x' : '-';
  str[4] = (mode & S_IRGRP) != 0 ? 'r' : '-';
  str[5] = (mode & S_IWGRP) != 0 ? 'w' : '-';
  str[6] = (mode & S_IXGRP) != 0 ? 'x' : '-';
  str[7] = (mode & S_IROTH) != 0 ? 'r' : '-';
  str[8] = (mode & S_IWOTH) != 0 ? 'w' : '-';
  str[9] = (mode & S_IXOTH) != 0 ? 'x' : '-';
  setst ((unsigned long) mode, str);
}