#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_13__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_3__ ccv_scd_param_t ;
typedef  int /*<<< orphan*/  ccv_scd_classifier_cascade_t ;
typedef  int /*<<< orphan*/  ccv_dense_matrix_t ;
struct TYPE_12__ {double confidence; } ;
struct TYPE_11__ {int x; int y; int width; int height; } ;
struct TYPE_14__ {TYPE_2__ classification; TYPE_1__ rect; } ;
typedef  TYPE_4__ ccv_comp_t ;
struct TYPE_15__ {int rnum; } ;
typedef  TYPE_5__ ccv_array_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CCV_IO_ANY_FILE ; 
 int CCV_IO_RGB_COLOR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccv_array_free (TYPE_5__*) ; 
 scalar_t__ ccv_array_get (TYPE_5__*,int) ; 
 int /*<<< orphan*/  ccv_disable_cache () ; 
 int /*<<< orphan*/  ccv_enable_default_cache () ; 
 int /*<<< orphan*/  ccv_matrix_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccv_read (char*,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  ccv_scd_classifier_cascade_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ccv_scd_classifier_cascade_read (char*) ; 
 TYPE_3__ ccv_scd_default_params ; 
 TYPE_5__* ccv_scd_detect_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,TYPE_3__) ; 
 int /*<<< orphan*/  ccv_size (int,int) ; 
 int /*<<< orphan*/  chdir (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 unsigned int get_current_time () ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ isspace (char) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main(int argc, char** argv)
{
	assert(argc >= 3);
	int i;
	ccv_enable_default_cache();
	ccv_dense_matrix_t* image = 0;
	ccv_scd_classifier_cascade_t* cascade = ccv_scd_classifier_cascade_read(argv[2]);
	ccv_read(argv[1], &image, CCV_IO_RGB_COLOR | CCV_IO_ANY_FILE);
	if (image != 0)
	{
		unsigned int elapsed_time = get_current_time();
		ccv_array_t* seq = ccv_scd_detect_objects(image, &cascade, 1, ccv_scd_default_params);
		elapsed_time = get_current_time() - elapsed_time;
		for (i = 0; i < seq->rnum; i++)
		{
			ccv_comp_t* comp = (ccv_comp_t*)ccv_array_get(seq, i);
			printf("%d %d %d %d %f\n", comp->rect.x, comp->rect.y, comp->rect.width, comp->rect.height, comp->classification.confidence);
		}
		printf("total : %d in time %dms\n", seq->rnum, elapsed_time);
		ccv_array_free(seq);
		ccv_matrix_free(image);
	} else {
		FILE* r = fopen(argv[1], "rt");
		if (argc == 4)
			chdir(argv[3]);
		if(r)
		{
			size_t len = 1024;
			char* file = (char*)malloc(len);
			ssize_t read;
			while((read = getline(&file, &len, r)) != -1)
			{
				while(read > 1 && isspace(file[read - 1]))
					read--;
				file[read] = 0;
				image = 0;
				ccv_read(file, &image, CCV_IO_RGB_COLOR | CCV_IO_ANY_FILE);
				assert(image != 0);
				ccv_scd_param_t params = ccv_scd_default_params;
				params.size = ccv_size(24, 24);
				ccv_array_t* seq = ccv_scd_detect_objects(image, &cascade, 1, params);
				printf("%s %d\n", file, seq->rnum);
				for (i = 0; i < seq->rnum; i++)
				{
					ccv_comp_t* comp = (ccv_comp_t*)ccv_array_get(seq, i);
					printf("%d %d %d %d %f\n", comp->rect.x, comp->rect.y, comp->rect.width, comp->rect.height, comp->classification.confidence);
				}
				ccv_array_free(seq);
				ccv_matrix_free(image);
			}
			free(file);
			fclose(r);
		}
	}
	ccv_scd_classifier_cascade_free(cascade);
	ccv_disable_cache();
	return 0;
}