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
typedef  int /*<<< orphan*/  ccv_bbf_classifier_cascade_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int ccv_bbf_classifier_cascade_write_binary (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * ccv_bbf_read_classifier_cascade (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,unsigned char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  write_c (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_json (int /*<<< orphan*/ *) ; 

int main(int argc, char** argv)
{
	assert(argc >= 3);
	ccv_bbf_classifier_cascade_t* cascade = ccv_bbf_read_classifier_cascade(argv[1]);
	if (strcmp(argv[2], "bin") == 0)
	{
		assert(argc >= 4);
		int len = ccv_bbf_classifier_cascade_write_binary(cascade, NULL, 0);
		char* s = malloc(len);
		ccv_bbf_classifier_cascade_write_binary(cascade, s, len);
		FILE* w = fopen(argv[3], "w");
		fwrite(s, 1, len, w);
		fclose(w);
		free(s);
	} else if (strcmp(argv[2], "c") == 0) {
		write_c(cascade);
	} else if (strcmp(argv[2], "json") == 0) {
		write_json(cascade);
	} else if (strcmp(argv[2], "cbin") == 0) {
		int len = ccv_bbf_classifier_cascade_write_binary(cascade, NULL, 0);
		char* s = malloc(len);
		ccv_bbf_classifier_cascade_write_binary(cascade, s, len);
		int i;
		for (i = 0; i < len; i++)
			printf("\\x%x", (unsigned char)s[i]);
		fflush(NULL);
		free(s);
	}
	return 0;
}