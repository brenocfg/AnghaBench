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
struct Exception {int /*<<< orphan*/  msg; int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  $ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  Exception_Backtrace () ; 
 int /*<<< orphan*/  File ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_to (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void Exception_Error(struct Exception* e)  {
  
  print_to($(File, stderr), 0, "\n");
  print_to($(File, stderr), 0, "!!\t\n");
  print_to($(File, stderr), 0, "!!\tUncaught %$\n", e->obj);
  print_to($(File, stderr), 0, "!!\t\n");
  print_to($(File, stderr), 0, "!!\t\t %s\n", e->msg);
  print_to($(File, stderr), 0, "!!\t\n");
  
  Exception_Backtrace();
  
  exit(EXIT_FAILURE);
  
}