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
 int /*<<< orphan*/  assert (int) ; 

int main(int argc, char** argv)
{
#ifdef HAVE_GSL
	assert(argc == 4);
	gsl_rng* rng = gsl_rng_alloc(gsl_rng_default);
	FILE* r = fopen(argv[1], "r");
	char* base_dir = argv[2];
	int dirlen = (base_dir != 0) ? strlen(base_dir) + 1 : 0;
	char* file = (char*)malloc(1024);
	int i = 0;
	ccv_rect_t rect;
	ccv_decimal_pose_t pose;
	// rect.x, rect.y, rect.width, rect.height roll pitch yaw
	while (fscanf(r, "%s %d %d %d %d %f %f %f", file, &rect.x, &rect.y, &rect.width, &rect.height, &pose.roll, &pose.pitch, &pose.yaw) != EOF)
	{
		if (pose.pitch < CCV_PI * 22.5 / 180 && pose.pitch > -CCV_PI * 22.5 / 180 &&
			pose.roll < CCV_PI * 22.5 / 180 && pose.roll > -CCV_PI * 22.5 / 180 &&
			pose.yaw < CCV_PI * 20 / 180 && pose.yaw > -CCV_PI * 20 / 180 &&
			rect.width >= 15 && rect.height >= 15)
		{
			// resize to a more proper sizes
			char* filename = (char*)malloc(1024);
			strncpy(filename, base_dir, 1024);
			filename[dirlen - 1] = '/';
			strncpy(filename + dirlen, file, 1024 - dirlen);
			ccv_dense_matrix_t* image = 0;
			ccv_read(filename, &image, CCV_IO_ANY_FILE | CCV_IO_GRAY);
			char* savefile = (char*)malloc(1024);
			ccv_dense_matrix_t* b = _ccv_aflw_slice_with_rect(rng, image, rect, ccv_size(48, 48), ccv_margin(0, 0, 0, 0), 10, 0.1, 0.05);
			snprintf(savefile, 1024, "%s/aflw-%07d-bw.png", argv[3], i);
			ccv_write(b, savefile, 0, CCV_IO_PNG_FILE, 0);
			ccv_matrix_free(b);
			ccv_matrix_free(image);
			image = 0;
			ccv_read(filename, &image, CCV_IO_ANY_FILE | CCV_IO_RGB_COLOR);
			b = _ccv_aflw_slice_with_rect(rng, image, rect, ccv_size(48, 48), ccv_margin(0, 0, 0, 0), 10, 0.1, 0.05);
			snprintf(savefile, 1024, "%s/aflw-%07d-rgb.png", argv[3], i);
			ccv_write(b, savefile, 0, CCV_IO_PNG_FILE, 0);
			ccv_matrix_free(b);
			ccv_matrix_free(image);
			i++;
			free(savefile);
			free(filename);
		}
	}
	fclose(r);
	free(file);
	gsl_rng_free(rng);
#else
	assert(0 && "aflw requires GSL library support");
#endif
	return 0;
}