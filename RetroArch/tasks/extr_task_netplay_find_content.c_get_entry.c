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
 char* path_basename (char const*) ; 
 int /*<<< orphan*/  path_remove_extension (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

__attribute__((used)) static void get_entry(char *entry, int len, const char *path)
{
   const char *buf = path_basename(path);
   entry[0]        = '\0';

   strlcpy(entry, buf, len);
   path_remove_extension(entry);
}