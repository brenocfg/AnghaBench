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
struct macro {int length; int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;
struct input {int input_left; int /*<<< orphan*/ * input_str; int /*<<< orphan*/ * input_ptr; int /*<<< orphan*/  input_macro; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  INPUT_STRING ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct input*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct input*) ; 
 int /*<<< orphan*/  inputs ; 
 int /*<<< orphan*/  link ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  report (char*) ; 

__attribute__((used)) static void
input_open_macro(struct macro *m)
{
	struct input *input;

	if ((input = malloc(sizeof(*input))) == NULL)
		report("%m");
	input->type = INPUT_STRING;
	input->input_macro = m->name;
	if ((input->input_str = malloc(m->length)) == NULL) {
		free(input);
		report("%m");
	}
	memcpy(input->input_str, m->value, m->length);
	input->input_ptr = input->input_str;
	input->input_left = m->length;
	LIST_INSERT_HEAD(&inputs, input, link);
}