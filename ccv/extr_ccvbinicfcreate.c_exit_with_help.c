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
	"\n  \033[1mUSAGE\033[0m\n\n    icfcreate [OPTION...]\n\n"
	"  \033[1mREQUIRED OPTIONS\033[0m\n\n"
	"    --positive-list : text file contains a list of positive files in format:\n"
	"                      <file name> center-x center-y horizontal-axis-length vertical-axis-length object-roll object-pitch object-yaw \\newline\n"
	"    --positive-count : the number of positive examples we should collect from positive files with certain distortion\n"
	"    --validate-list : text file contains a list of positive files in following format but only used for soft cascading:\n"
	"                      <file name> center-x center-y horizontal-axis-length vertical-axis-length object-roll object-pitch object-yaw \\newline\n"
	"    --acceptance : what percentage of validate examples that we should accept for soft cascading\n"
	"    --background-list : text file contains a list of image files that don't contain any target objects\n"
	"    --negative-count : the number of negative examples we should collect from background files for boosting\n"
	"    --size : size of object in pixel formatted as WxH\n"
	"    --feature-size : the number of features that we randomly generates and later pooling from\n"
	"    --weak-classifier-count : the number of weak classifiers in the boosted model\n"
	"    --working-dir : the directory to save progress and produce result model\n\n"
	"  \033[1mOTHER OPTIONS\033[0m\n\n"
	"    --base-dir : change the base directory so that the program can read images from there\n"
	"    --grayscale : 0 or 1, whether to exploit color in a given image [DEFAULT TO 0]\n"
	"    --margin : margin for object when extracting from given images, formatted as left,top,right,bottom\n"
	"    --deform-shift : translation distortion range in pixels [DEFAULT TO 1]\n"
	"    --deform-angle : rotation distortion range in degrees [DEFAULT TO 0]\n"
	"    --deform-scale : scale distortion range [DEFAULT TO 0.075]\n"
	"    --min-dimension : the minimum dimension of one icf feature [DEFAULT TO 2]\n"
	"    --bootstrap : the number of bootstrap stages for negative example generations [DEFAULT TO 3]\n\n"
	);
	exit(-1);
}