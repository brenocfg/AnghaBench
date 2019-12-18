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
 int /*<<< orphan*/  _getcwd (char*,int) ; 
 int /*<<< orphan*/  getwd (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

void Q_getwd (char *out)
{
	int i = 0;

#ifdef WIN32
   _getcwd (out, 256);
   strcat (out, "\\");
#else
   getwd (out);
   strcat (out, "/");
#endif

   while ( out[i] != 0 )
   {
	   if ( out[i] == '\\' )
		   out[i] = '/';
	   i++;
   }
}