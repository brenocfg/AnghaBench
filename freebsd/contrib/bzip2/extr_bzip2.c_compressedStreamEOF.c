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
 scalar_t__ noisy ; 
 int /*<<< orphan*/  perror (char*) ; 
 char* progName ; 
 int /*<<< orphan*/  showFileNames () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static 
void compressedStreamEOF ( void )
{
  if (noisy) {
    fprintf ( stderr,
	      "\n%s: Compressed file ends unexpectedly;\n\t"
	      "perhaps it is corrupted?  *Possible* reason follows.\n",
	      progName );
    perror ( progName );
    showFileNames();
    cadvise();
  }
  cleanUpAndFail( 2 );
}