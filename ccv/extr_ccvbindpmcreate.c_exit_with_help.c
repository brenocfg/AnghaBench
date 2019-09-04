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
	"\n  \033[1mUSAGE\033[0m\n\n    dpmcreate [OPTION...]\n\n"
	"  \033[1mREQUIRED OPTIONS\033[0m\n\n"
	"    --positive-list : text file contains a list of positive files in format:\n"
	"                      <file name> x y width height \\newline\n"
	"    --background-list : text file contains a list of image files that don't contain any target objects\n"
	"    --negative-count : the number of negative examples we should collect from background files to initialize SVM\n"
	"    --model-component : the number of root filters in our mixture model\n"
	"    --model-part : the number of part filters for each root filter\n"
	"    --working-dir : the directory to save progress and produce result model\n"
	"    --symmetric : 0 or 1, whether to exploit symmetric property of the object\n\n"
	"  \033[1mOTHER OPTIONS\033[0m\n\n"
	"    --base-dir : change the base directory so that the program can read images from there\n"
	"    --iterations : how many iterations are needed for stochastic gradient descent [DEFAULT TO 1000]\n"
	"    --root-relabels : how many relabel procedures are needed for root model optimization [DEFAULT TO 20]\n"
	"    --data-minings : how many data mining procedures are needed for discovering hard examples [DEFAULT TO 50]\n"
	"    --relabels : how many relabel procedures are needed for part model optimization [DEFAULT TO 10]\n"
	"    --alpha : the step size for stochastic gradient descent [DEFAULT TO 0.01]\n"
	"    --alpha-ratio : decrease the step size for each iteration [DEFAULT TO 0.995]\n"
	"    --margin-c : the famous C in SVM [DEFAULT TO 0.002]\n"
	"    --balance : to balance the weight of positive examples and negative examples [DEFAULT TO 1.5]\n"
	"    --negative-cache-size : the cache size for negative examples it should be smaller than negative-count and larger than 100 [DEFAULT TO 2000]\n"
	"    --include-overlap : the percentage of overlap between expected bounding box and the bounding box from detection. Beyond this threshold, it is ensured to be the same object [DEFAULT TO 0.7]\n"
	"    --grayscale : 0 or 1, whether to exploit color in a given image [DEFAULT TO 0]\n"
	"    --discard-estimating-constant : 0 or 1, when estimating bounding boxes, discarding constant (which may be accumulated error) [DEFAULT TO 1]\n"
	"    --percentile-breakdown : 0.00 - 1.00, the percentile use for breakdown threshold [DEFAULT TO 0.05]\n\n"
	);
	exit(-1);
}