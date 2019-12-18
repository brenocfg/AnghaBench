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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void exit_with_help(void)
{
	printf(
	"\n  \033[1mUSAGE\033[0m\n\n    swtreate input-text [OPTION...]\n\n"
	"  \033[1mARGUMENTS\033[0m\n\n"
	"    input-text: text file contains a list of text locations in format:\n"
	"                <file name>\\newline\n"
	"                x y width height <of one text location>\\newline\n"
	"                x y width height <of another text location>\\newline\n\n"
	"  \033[1mOPTIONS\033[0m\n\n"
	"    --size : the window size of canny filter [DEFAULT TO 1,2,3]\n"
	"    --low-thresh : the low threshold of canny filter [DEFAULT TO 50,1,150]\n"
	"    --high-thresh : the high threshold of canny filter [DEFAULT TO 200,1,350]\n"
	"    --max-height : the maximal height of letter [DEFAULT TO 500,1,500]\n"
	"    --min-height : the minimal height of letter [DEFAULT TO 5,1,30]\n"
	"    --min-area : the minimal area of letter [DEFAULT TO 10,1,100]\n"
	"    --aspect-ratio : the aspect ratio of letter [DEFAULT TO 5,1,15]\n"
	"    --std-ratio : the maximal std to mean ratio of letter [DEFAULT TO 0.1,0.01,1.0]\n"
	"    --thickness-ratio : the maximal allowance of thickness change between two letters [DEFAULT TO 1,0.1,2]\n"
	"    --height-ratio : the maximal allowance of height change between two letters [DEFAULT TO 1,0.1,3]\n"
	"    --intensity-thresh : how much intensity tolerance between two letters [DEFAULT TO 1,1,50]\n"
	"    --letter-occlude-thresh : how many letters one letter rectangle can occlude [DEFAULT TO 0,1,5]\n"
	"    --distance-ratio : the distance between two letters comparing to their width [DEFAULT TO 1,0.1,5]\n"
	"    --intersect-ratio : how much in the y-axis two letters intersect with each other [DEFAULT TO 0,0.1,5]\n"
	"    --letter-thresh : how many letters in minimal should one text line contains [DEFAULT TO 0,1,5]\n"
	"    --elongate-ratio : what's the minimal ratio between text line's width and height [DEFAULT TO 0.1,0.1,2.5]\n"
	"    --breakdown-ratio : what's the ratio for text line to break down into words [DEFAULT TO 0.5,0.01,1.5]\n"
	"    --breakdown : support to break text lines down to words [DEFAULT TO 1]\n"
	"    --iterations : how many iterations for the search [DEFAULT TO 10]\n"
	"    --base-dir : change the base directory so that the program can read images from there\n"
	);
	exit(-1);
}