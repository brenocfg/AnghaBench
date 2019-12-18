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

/* Variables and functions */
 int /*<<< orphan*/  cleanUpAndFail (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 char* progName ; 
 int /*<<< orphan*/  showFileNames () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static 
void panic ( const Char* s )
{
   fprintf ( stderr,
             "\n%s: PANIC -- internal consistency error:\n"
             "\t%s\n"
             "\tThis is a BUG.  Please report it to:\n"
             "\tbzip2-devel@sourceware.org\n",
             progName, s );
   showFileNames();
   cleanUpAndFail( 3 );
}