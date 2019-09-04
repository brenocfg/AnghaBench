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
struct option {char* member_0; int member_1; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; } ;
typedef  int /*<<< orphan*/  ccv_cnnp_dataframe_t ;

/* Variables and functions */
 int /*<<< orphan*/ * _dataframe_from_disk_new (char*,char*) ; 
 int /*<<< orphan*/  ccv_cnnp_dataframe_free (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  ccv_nnc_init () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt_long_only (int,char**,char*,struct option*,int*) ; 
 char* optarg ; 
 int /*<<< orphan*/  train_imagenet (int,int /*<<< orphan*/ * const,int /*<<< orphan*/ * const) ; 

int main(int argc, char** argv)
{
	ccv_nnc_init();
	static struct option imagenet_options[] = {
		/* help */
		{"help", 0, 0, 0},
		/* required parameters */
		{"train-list", 1, 0, 0},
		{"test-list", 1, 0, 0},
		/* optional parameters */
		{"base-dir", 1, 0, 0},
		{0, 0, 0, 0}
	};
	int c;
	char* train_list = 0;
	char* test_list = 0;
	char* base_dir = 0;
	while (getopt_long_only(argc, argv, "", imagenet_options, &c) != -1)
	{
		switch (c)
		{
			case 0:
				exit(0);
			case 1:
				train_list = optarg;
				break;
			case 2:
				test_list = optarg;
				break;
			case 3:
				base_dir = optarg;
				break;
		}
	}
	ccv_cnnp_dataframe_t* const train_data = _dataframe_from_disk_new(train_list, base_dir);
	ccv_cnnp_dataframe_t* const test_data = _dataframe_from_disk_new(test_list, base_dir);
	train_imagenet(256, train_data, test_data);
	ccv_cnnp_dataframe_free(train_data);
	ccv_cnnp_dataframe_free(test_data);
	return 0;
}