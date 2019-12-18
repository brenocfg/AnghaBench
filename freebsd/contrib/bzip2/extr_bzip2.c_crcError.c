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
 int /*<<< orphan*/  cadvise () ; 
 int /*<<< orphan*/  cleanUpAndFail (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* progName ; 
 int /*<<< orphan*/  showFileNames () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static 
void crcError ( void )
{
   fprintf ( stderr,
             "\n%s: Data integrity error when decompressing.\n",
             progName );
   showFileNames();
   cadvise();
   cleanUpAndFail( 2 );
}