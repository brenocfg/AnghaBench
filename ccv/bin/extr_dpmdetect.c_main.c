#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_14__ {double confidence; } ;
struct TYPE_15__ {int x; int y; int width; int height; } ;
struct TYPE_16__ {int pnum; TYPE_3__* part; TYPE_4__ classification; TYPE_5__ rect; } ;
typedef  TYPE_6__ ccv_root_comp_t ;
typedef  int /*<<< orphan*/  ccv_dpm_mixture_model_t ;
typedef  int /*<<< orphan*/  ccv_dense_matrix_t ;
struct TYPE_17__ {int rnum; } ;
typedef  TYPE_7__ ccv_array_t ;
struct TYPE_12__ {double confidence; } ;
struct TYPE_11__ {int x; int y; int width; int height; } ;
struct TYPE_13__ {TYPE_2__ classification; TYPE_1__ rect; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CCV_IO_ANY_FILE ; 
 int CCV_IO_GRAY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccv_array_free (TYPE_7__*) ; 
 scalar_t__ ccv_array_get (TYPE_7__*,int) ; 
 int /*<<< orphan*/  ccv_dpm_default_params ; 
 TYPE_7__* ccv_dpm_detect_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_dpm_mixture_model_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ccv_dpm_read_mixture_model (char*) ; 
 int /*<<< orphan*/  ccv_drain_cache () ; 
 int /*<<< orphan*/  ccv_enable_default_cache () ; 
 int /*<<< orphan*/  ccv_matrix_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccv_read (char*,int /*<<< orphan*/ **,int) ; 
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
	int i, j;
	ccv_enable_default_cache();
	ccv_dense_matrix_t* image = 0;
	ccv_read(argv[1], &image, CCV_IO_ANY_FILE);
	ccv_dpm_mixture_model_t* model = ccv_dpm_read_mixture_model(argv[2]);
	if (image != 0)
	{
		unsigned int elapsed_time = get_current_time();
		ccv_array_t* seq = ccv_dpm_detect_objects(image, &model, 1, ccv_dpm_default_params);
		elapsed_time = get_current_time() - elapsed_time;
		if (seq)
		{
			for (i = 0; i < seq->rnum; i++)
			{
				ccv_root_comp_t* comp = (ccv_root_comp_t*)ccv_array_get(seq, i);
				printf("%d %d %d %d %f %d\n", comp->rect.x, comp->rect.y, comp->rect.width, comp->rect.height, comp->classification.confidence, comp->pnum);
				for (j = 0; j < comp->pnum; j++)
					printf("| %d %d %d %d %f\n", comp->part[j].rect.x, comp->part[j].rect.y, comp->part[j].rect.width, comp->part[j].rect.height, comp->part[j].classification.confidence);
			}
			printf("total : %d in time %dms\n", seq->rnum, elapsed_time);
			ccv_array_free(seq);
		} else {
			printf("elapsed time %dms\n", elapsed_time);
		}
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
				ccv_read(file, &image, CCV_IO_GRAY | CCV_IO_ANY_FILE);
				assert(image != 0);
				ccv_array_t* seq = ccv_dpm_detect_objects(image, &model, 1, ccv_dpm_default_params);
				if (seq != 0)
				{
					for (i = 0; i < seq->rnum; i++)
					{
						ccv_root_comp_t* comp = (ccv_root_comp_t*)ccv_array_get(seq, i);
						printf("%s %d %d %d %d %f %d\n", file, comp->rect.x, comp->rect.y, comp->rect.width, comp->rect.height, comp->classification.confidence, comp->pnum);
						for (j = 0; j < comp->pnum; j++)
							printf("| %d %d %d %d %f\n", comp->part[j].rect.x, comp->part[j].rect.y, comp->part[j].rect.width, comp->part[j].rect.height, comp->part[j].classification.confidence);
					}
					ccv_array_free(seq);
				}
				ccv_matrix_free(image);
			}
			free(file);
			fclose(r);
		}
	}
	ccv_drain_cache();
	ccv_dpm_mixture_model_free(model);
	return 0;
}