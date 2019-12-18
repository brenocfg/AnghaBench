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
typedef  char UCHAR ;

/* Variables and functions */
 int TRUE ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int Config_FileGetParameter(UCHAR *string, UCHAR *dest,UCHAR *source)
{
  UCHAR buf1[100];
  int source_len = strlen(source);

    memset(buf1,0,100);
    strcat(buf1, string);
    strcat(buf1, "=");
    source+=strlen(buf1);

   memcpy(dest,source,source_len-strlen(buf1));
 return TRUE;
}