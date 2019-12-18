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
 int /*<<< orphan*/  DEFAULT ; 
 int /*<<< orphan*/  RED ; 
#define  SIGFPE 130 
#define  SIGILL 129 
#define  SIGSEGV 128 
 char* assert_err ; 
 int /*<<< orphan*/  assert_err_buff ; 
 int assert_err_num ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  pt_color (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcat (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_passing ; 

__attribute__((used)) static void ptest_signal(int sig) {

  test_passing = 0;
  
  switch( sig ) {
    case SIGFPE:  sprintf(assert_err_buff,
      "        %i. Division by Zero\n", assert_err_num+1);
    break;
    case SIGILL:  sprintf(assert_err_buff,
      "        %i. Illegal Instruction\n", assert_err_num+1);
    break;
    case SIGSEGV: sprintf(assert_err_buff,
      "        %i. Segmentation Fault\n", assert_err_num+1);
    break;
  }
  
  assert_err_num++;
  strcat(assert_err, assert_err_buff);
  
  pt_color(RED); 
  printf("Failed! \n\n%s\n", assert_err);
  pt_color(DEFAULT);
  
  puts("    | Stopping Execution.");
  fflush(stdout);
  exit(0);
  
}