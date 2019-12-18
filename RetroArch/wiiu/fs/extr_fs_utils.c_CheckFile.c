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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  dirnoslash ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char const*) ; 
 char* strrchr (char*,char) ; 

int CheckFile(const char * filepath)
{
   struct stat filestat;
   char *notRoot        = NULL;

   if (!filepath)
      return 0;

   char dirnoslash[strlen(filepath)+2];

   snprintf(dirnoslash, sizeof(dirnoslash), "%s", filepath);

   while(dirnoslash[strlen(dirnoslash)-1] == '/')
      dirnoslash[strlen(dirnoslash)-1] = '\0';

   notRoot = strrchr(dirnoslash, '/');
   if (!notRoot)
      strcat(dirnoslash, "/");

   if (stat(dirnoslash, &filestat) == 0)
      return 1;

   return 0;
}