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
 int FALSE ; 
 int /*<<< orphan*/  NSTREQ (char*,char*,int) ; 
 int TRUE ; 
 int strlen (char*) ; 

__attribute__((used)) static int
directory_prefix(char *pref, char *dir)
{
  int len = strlen(pref);

  if (!NSTREQ(pref, dir, len))
    return FALSE;
  if (dir[len] == '/' || dir[len] == '\0')
    return TRUE;
  return FALSE;
}