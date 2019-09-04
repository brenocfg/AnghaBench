#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int noctaves; int nlevels; int up2x; int edge_threshold; int /*<<< orphan*/  peak_threshold; int /*<<< orphan*/  norm_threshold; } ;
typedef  TYPE_2__ ccv_sift_param_t ;
struct TYPE_16__ {double x; double y; } ;
typedef  TYPE_3__ ccv_keypoint_t ;
struct TYPE_14__ {float* f32; } ;
struct TYPE_17__ {int cols; int rows; TYPE_1__ data; } ;
typedef  TYPE_4__ ccv_dense_matrix_t ;
struct TYPE_18__ {int rnum; } ;
typedef  TYPE_5__ ccv_array_t ;

/* Variables and functions */
 int CCV_IO_ANY_FILE ; 
 int CCV_IO_GRAY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccv_array_free (TYPE_5__*) ; 
 scalar_t__ ccv_array_get (TYPE_5__*,int) ; 
 int /*<<< orphan*/  ccv_disable_cache () ; 
 int /*<<< orphan*/  ccv_enable_default_cache () ; 
 int /*<<< orphan*/  ccv_matrix_free (TYPE_4__*) ; 
 int /*<<< orphan*/  ccv_read (char*,TYPE_4__**,int) ; 
 int /*<<< orphan*/  ccv_sift (TYPE_4__*,TYPE_5__**,TYPE_4__**,int /*<<< orphan*/ ,TYPE_2__) ; 
 unsigned int get_current_time () ; 
 int /*<<< orphan*/  printf (char*,unsigned int,...) ; 

int main(int argc, char** argv)
{
	assert(argc == 3);
	ccv_enable_default_cache();
	ccv_dense_matrix_t* object = 0;
	ccv_dense_matrix_t* image = 0;
	ccv_read(argv[1], &object, CCV_IO_GRAY | CCV_IO_ANY_FILE);
	ccv_read(argv[2], &image, CCV_IO_GRAY | CCV_IO_ANY_FILE);
	unsigned int elapsed_time = get_current_time();
	ccv_sift_param_t params = {
		.noctaves = 3,
		.nlevels = 6,
		.up2x = 1,
		.edge_threshold = 10,
		.norm_threshold = 0,
		.peak_threshold = 0,
	};
	ccv_array_t* obj_keypoints = 0;
	ccv_dense_matrix_t* obj_desc = 0;
	ccv_sift(object, &obj_keypoints, &obj_desc, 0, params);
	ccv_array_t* image_keypoints = 0;
	ccv_dense_matrix_t* image_desc = 0;
	ccv_sift(image, &image_keypoints, &image_desc, 0, params);
	elapsed_time = get_current_time() - elapsed_time;
	int i, j, k;
	int match = 0;
	for (i = 0; i < obj_keypoints->rnum; i++)
	{
		float* odesc = obj_desc->data.f32 + i * 128;
		int minj = -1;
		double mind = 1e6, mind2 = 1e6;
		for (j = 0; j < image_keypoints->rnum; j++)
		{
			float* idesc = image_desc->data.f32 + j * 128;
			double d = 0;
			for (k = 0; k < 128; k++)
			{
				d += (odesc[k] - idesc[k]) * (odesc[k] - idesc[k]);
				if (d > mind2)
					break;
			}
			if (d < mind)
			{
				mind2 = mind;
				mind = d;
				minj = j;
			} else if (d < mind2) {
				mind2 = d;
			}
		}
		if (mind < mind2 * 0.36)
		{
			ccv_keypoint_t* op = (ccv_keypoint_t*)ccv_array_get(obj_keypoints, i);
			ccv_keypoint_t* kp = (ccv_keypoint_t*)ccv_array_get(image_keypoints, minj);
			printf("%f %f => %f %f\n", op->x, op->y, kp->x, kp->y);
			match++;
		}
	}
	printf("%dx%d on %dx%d\n", object->cols, object->rows, image->cols, image->rows);
	printf("%d keypoints out of %d are matched\n", match, obj_keypoints->rnum);
	printf("elpased time : %d\n", elapsed_time);
	ccv_array_free(obj_keypoints);
	ccv_array_free(image_keypoints);
	ccv_matrix_free(obj_desc);
	ccv_matrix_free(image_desc);
	ccv_matrix_free(object);
	ccv_matrix_free(image);
	ccv_disable_cache();
	return 0;
}