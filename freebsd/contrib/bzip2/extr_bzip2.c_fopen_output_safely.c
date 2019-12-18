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
typedef  int IntNative ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int O_CREAT ; 
 int O_EXCL ; 
 int O_WRONLY ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/ * fdopen (int,char const*) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ *,char const*) ; 
 int open (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static
FILE* fopen_output_safely ( Char* name, const char* mode )
{
#  if BZ_UNIX
   FILE*     fp;
   IntNative fh;
   fh = open(name, O_WRONLY|O_CREAT|O_EXCL, S_IWUSR|S_IRUSR);
   if (fh == -1) return NULL;
   fp = fdopen(fh, mode);
   if (fp == NULL) close(fh);
   return fp;
#  else
   return fopen(name, mode);
#  endif
}