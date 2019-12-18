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
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int stub1 (char*) ; 
 int stub2 (char*) ; 

void label_sanitize(char *label, bool (*left)(char*), bool (*right)(char*))
{
   bool copy = true;
   int rindex = 0;
   int lindex = 0;
   char new_label[PATH_MAX_LENGTH];

   for (; lindex < PATH_MAX_LENGTH && label[lindex] != '\0'; lindex++)
   {
      if (copy)
      {
         /* check for the start of the range */
         if ((*left)(&label[lindex]))
            copy = false;

         if (copy)
            new_label[rindex++] = label[lindex];
      }
      else if ((*right)(&label[lindex]))
         copy = true;
   }

   new_label[rindex] = '\0';

   strlcpy(label, new_label, PATH_MAX_LENGTH);
}