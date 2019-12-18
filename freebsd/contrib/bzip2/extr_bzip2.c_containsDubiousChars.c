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
typedef  char Char ;
typedef  int /*<<< orphan*/  Bool ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  True ; 

__attribute__((used)) static 
Bool containsDubiousChars ( Char* name )
{
#  if BZ_UNIX
   /* On unix, files can contain any characters and the file expansion
    * is performed by the shell.
    */
   return False;
#  else /* ! BZ_UNIX */
   /* On non-unix (Win* platforms), wildcard characters are not allowed in 
    * filenames.
    */
   for (; *name != '\0'; name++)
      if (*name == '?' || *name == '*') return True;
   return False;
#  endif /* BZ_UNIX */
}