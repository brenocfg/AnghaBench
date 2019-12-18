#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* filename; } ;
typedef  TYPE_1__ ccv_file_info_t ;
typedef  int /*<<< orphan*/  ccv_categorized_t ;
typedef  int /*<<< orphan*/  ccv_array_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccmalloc (int) ; 
 int /*<<< orphan*/ * ccv_array_new (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_array_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccv_categorized (int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const* const,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fscanf (int /*<<< orphan*/ *,char*,int*,char*) ; 
 scalar_t__ malloc (int) ; 
 int strlen (char const* const) ; 
 int /*<<< orphan*/  strncpy (char*,char const* const,int) ; 

__attribute__((used)) static ccv_array_t* _array_from_disk_new(const char* const list, const char* const base_dir)
{
	FILE *r = fopen(list, "r");
	assert(r && "list doesn't exists");
	int dirlen = (base_dir != 0) ? strlen(base_dir) + 1 : 0;
	ccv_array_t* categorizeds = ccv_array_new(sizeof(ccv_categorized_t), 64, 0);
	int c;
	char* file = (char*)malloc(1024);
	while (fscanf(r, "%d %s", &c, file) != EOF)
	{
		char* filename = (char*)ccmalloc(1024);
		if (base_dir != 0)
		{
			strncpy(filename, base_dir, 1024);
			filename[dirlen - 1] = '/';
		}
		strncpy(filename + dirlen, file, 1024 - dirlen);
		ccv_file_info_t file_info = {
			.filename = filename,
		};
		// imageNet's category class starts from 1, thus, minus 1 to get 0-index
		ccv_categorized_t categorized = ccv_categorized(c - 1, 0, &file_info);
		ccv_array_push(categorizeds, &categorized);
	}
	free(file);
	fclose(r);
	return categorizeds;
}