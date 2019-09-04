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
 char* _ (char*) ; 
 scalar_t__ column ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,int,scalar_t__) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int line ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void conversion_error_EILSEQ (const char* infilename)
{
  fflush(stdout);
  if (column > 0)
    putc('\n',stderr);
  error(0,0,
        /* TRANSLATORS: An error message.
           The placeholders expand to the input file name, a line number, and a column number.  */
        _("%s:%u:%u: cannot convert"),
        infilename,line,column);
}