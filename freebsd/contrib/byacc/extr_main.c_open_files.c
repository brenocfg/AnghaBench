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
 void* action_file ; 
 scalar_t__ code_file ; 
 int /*<<< orphan*/  code_file_name ; 
 int /*<<< orphan*/  create_file_names () ; 
 scalar_t__ defines_file ; 
 int /*<<< orphan*/  defines_file_name ; 
 scalar_t__ dflag ; 
 scalar_t__ externs_file ; 
 int /*<<< orphan*/  externs_file_name ; 
 char* file_prefix ; 
 scalar_t__ fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 scalar_t__ gflag ; 
 scalar_t__ graph_file ; 
 int /*<<< orphan*/  graph_file_name ; 
 scalar_t__ iflag ; 
 scalar_t__ input_file ; 
 int /*<<< orphan*/  input_file_name ; 
 int /*<<< orphan*/  open_error (int /*<<< orphan*/ ) ; 
 void* open_tmpfile (char*) ; 
 scalar_t__ output_file ; 
 int /*<<< orphan*/  output_file_name ; 
 scalar_t__ rflag ; 
 void* text_file ; 
 void* union_file ; 
 scalar_t__ verbose_file ; 
 int /*<<< orphan*/  verbose_file_name ; 
 scalar_t__ vflag ; 

__attribute__((used)) static void
open_files(void)
{
    create_file_names();

    if (input_file == 0)
    {
	input_file = fopen(input_file_name, "r");
	if (input_file == 0)
	    open_error(input_file_name);
    }

    action_file = open_tmpfile("action_file");
    text_file = open_tmpfile("text_file");

    if (vflag)
    {
	verbose_file = fopen(verbose_file_name, "w");
	if (verbose_file == 0)
	    open_error(verbose_file_name);
    }

    if (gflag)
    {
	graph_file = fopen(graph_file_name, "w");
	if (graph_file == 0)
	    open_error(graph_file_name);
	fprintf(graph_file, "digraph %s {\n", file_prefix);
	fprintf(graph_file, "\tedge [fontsize=10];\n");
	fprintf(graph_file, "\tnode [shape=box,fontsize=10];\n");
	fprintf(graph_file, "\torientation=landscape;\n");
	fprintf(graph_file, "\trankdir=LR;\n");
	fprintf(graph_file, "\t/*\n");
	fprintf(graph_file, "\tmargin=0.2;\n");
	fprintf(graph_file, "\tpage=\"8.27,11.69\"; // for A4 printing\n");
	fprintf(graph_file, "\tratio=auto;\n");
	fprintf(graph_file, "\t*/\n");
    }

    if (dflag)
    {
	defines_file = fopen(defines_file_name, "w");
	if (defines_file == 0)
	    open_error(defines_file_name);
	union_file = open_tmpfile("union_file");
    }

    if (iflag)
    {
	externs_file = fopen(externs_file_name, "w");
	if (externs_file == 0)
	    open_error(externs_file_name);
    }

    output_file = fopen(output_file_name, "w");
    if (output_file == 0)
	open_error(output_file_name);

    if (rflag)
    {
	code_file = fopen(code_file_name, "w");
	if (code_file == 0)
	    open_error(code_file_name);
    }
    else
	code_file = output_file;
}