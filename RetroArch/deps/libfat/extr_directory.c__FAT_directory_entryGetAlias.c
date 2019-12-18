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
typedef  char u8 ;

/* Variables and functions */
 char const CASE_LOWER_BASE ; 
 char const CASE_LOWER_EXT ; 
 char const DIR_ENTRY_FREE ; 
 size_t DIR_ENTRY_caseInfo ; 
 size_t DIR_ENTRY_extension ; 
 int DIR_ENTRY_name ; 
 char tolower (unsigned char) ; 

__attribute__((used)) static bool _FAT_directory_entryGetAlias (const u8* entryData, char* destName)
{
   char c;
   bool caseInfo;
   int i = 0;
   int j = 0;

   destName[0] = '\0';
   if (entryData[0] != DIR_ENTRY_FREE)
   {
      if (entryData[0] == '.')
      {
         destName[0] = '.';
         if (entryData[1] == '.')
         {
            destName[1] = '.';
            destName[2] = '\0';
         }
         else
            destName[1] = '\0';
      }
      else
      {
         /* Copy the filename from the dirEntry to the string */
         caseInfo = entryData[DIR_ENTRY_caseInfo] & CASE_LOWER_BASE;
         for (i = 0; (i < 8) && (entryData[DIR_ENTRY_name + i] != ' '); i++)
         {
            c = entryData[DIR_ENTRY_name + i];
            destName[i] = (caseInfo ? tolower((unsigned char)c) : c);
         }
         /* Copy the extension from the dirEntry to the string */
         if (entryData[DIR_ENTRY_extension] != ' ')
         {
            destName[i++] = '.';
            caseInfo = entryData[DIR_ENTRY_caseInfo] & CASE_LOWER_EXT;
            for ( j = 0; (j < 3) && (entryData[DIR_ENTRY_extension + j] != ' '); j++)
            {
               c = entryData[DIR_ENTRY_extension + j];
               destName[i++] = (caseInfo ? tolower((unsigned char)c) : c);
            }
         }
         destName[i] = '\0';
      }
   }

   return (destName[0] != '\0');
}