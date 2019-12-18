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
struct arguments {char* member_1; char* member_2; int member_7; int member_8; int member_9; int member_10; int member_13; int member_14; int member_18; scalar_t__ isDumpIn; scalar_t__ abort; int /*<<< orphan*/  member_17; int /*<<< orphan*/ * member_16; int /*<<< orphan*/  member_15; int /*<<< orphan*/  member_12; int /*<<< orphan*/  member_11; int /*<<< orphan*/ * member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/ * member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_DUMP_FILE ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  INT64_MAX ; 
 int /*<<< orphan*/  argp ; 
 int /*<<< orphan*/  argp_parse (int /*<<< orphan*/ *,int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arguments*) ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ taosCheckParam (struct arguments*) ; 
 scalar_t__ taosDumpIn (struct arguments*) ; 
 scalar_t__ taosDumpOut (struct arguments*) ; 

int main(int argc, char *argv[]) {
  struct arguments arguments = {
    // connection option
    NULL, "root", "taosdata", 0,
    // output file
    DEFAULT_DUMP_FILE, DEFAULT_DUMP_FILE, NULL,
    // dump unit option
    false, false,
    // dump format option
    false, false, 0, INT64_MAX, 1, false,
    // other options
    0, NULL, 0, false};

  /* Parse our arguments; every option seen by parse_opt will be
     reflected in arguments. */
  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  if (arguments.abort) error(10, 0, "ABORTED");

  if (taosCheckParam(&arguments) < 0) {
    exit(EXIT_FAILURE);
  }

  if (arguments.isDumpIn) {
    if (taosDumpIn(&arguments) < 0) return -1;
  } else {
    if (taosDumpOut(&arguments) < 0) return -1;
  }

  return 0;
}