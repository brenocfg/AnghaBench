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
typedef  int /*<<< orphan*/  XML_Char ;

/* Variables and functions */
 int /*<<< orphan*/  T (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  ftprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(const XML_Char *prog, int rc)
{
  ftprintf(stderr,
           T("usage: %s [-s] [-n] [-p] [-x] [-e encoding] [-w] [-d output-dir] [-c] [-m] [-r] [-t] [-N] [file ...]\n"), prog);
  exit(rc);
}