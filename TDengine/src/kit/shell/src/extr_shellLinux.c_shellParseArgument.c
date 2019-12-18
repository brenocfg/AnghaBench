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
struct arguments {scalar_t__ abort; } ;

/* Variables and functions */
 int /*<<< orphan*/  argp ; 
 int /*<<< orphan*/  argp_parse (int /*<<< orphan*/ *,int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arguments*) ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 

void shellParseArgument(int argc, char *argv[], struct arguments *arguments) {
  argp_parse(&argp, argc, argv, 0, 0, arguments);
  if (arguments->abort) {
    error(10, 0, "ABORTED");
  }
}