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
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void exit_with_help(void)
{
	printf(
	"\n  \033[1mUSAGE\033[0m\n\n    image-net [OPTION...]\n\n"
	"  \033[1mREQUIRED OPTIONS\033[0m\n\n"
	"    --train-list : text file contains a list of image files in format:\n"
	"                      class-label <file name>\\newline\n"
	"    --test-list : text file contains a list of image files in format:\n"
	"                      class-label <file name>\\newline\n"
	"    --working-dir : the directory to save progress and produce result model\n\n"
	"  \033[1mOTHER OPTIONS\033[0m\n\n"
	"    --base-dir : change the base directory so that the program can read images from there\n"
	"    --max-epoch : how many epoch are needed for stochastic gradient descent (an epoch corresponds to go through the full train list) [DEFAULT TO 100]\n"
	"    --iterations : how many iterations are needed for stochastic gradient descent (an iteration corresponds to go through a mini batch) [DEFAULT TO 5000]\n\n"
	);
	exit(0);
}