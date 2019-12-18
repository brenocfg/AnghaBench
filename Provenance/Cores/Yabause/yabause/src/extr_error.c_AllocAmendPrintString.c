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
 int /*<<< orphan*/  YuiErrorMsg (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void AllocAmendPrintString(const char *string1, const char *string2)
{
   char *string;

   if ((string = (char *)malloc(strlen(string1) + strlen(string2) + 2)) == NULL)
      return;

   sprintf(string, "%s%s\n", string1, string2);
   YuiErrorMsg(string);

   free(string);
}