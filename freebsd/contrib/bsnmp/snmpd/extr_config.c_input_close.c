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
struct input {int type; struct input* input_str; struct input* input_filename; int /*<<< orphan*/  input_fp; } ;

/* Variables and functions */
#define  INPUT_FILE 129 
#define  INPUT_STRING 128 
 struct input* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct input*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct input*) ; 
 int /*<<< orphan*/  inputs ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static void
input_close(void)
{
	struct input *input;

	if ((input = LIST_FIRST(&inputs)) == NULL)
		abort();
	switch (input->type) {

	  case INPUT_FILE:
		fclose(input->input_fp);
		free(input->input_filename);
		break;

	  case INPUT_STRING:
		free(input->input_str);
		break;
	}
	LIST_REMOVE(input, link);
	free(input);
}