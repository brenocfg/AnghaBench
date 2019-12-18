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
 int /*<<< orphan*/  T_EXPECT_EQ_INT (int,int,char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  read (int,int*,int) ; 

__attribute__((used)) static void do_child(int *pipefd){
	int exit = 0;

	close(pipefd[1]);
	read(pipefd[0], &exit, sizeof(int));
	T_QUIET; T_EXPECT_EQ_INT(exit, 1, "exit");
	close(pipefd[0]);
}