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
struct arg_hdr {int dummy; } ;
struct arg_end {int count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_EMALLOC ; 
 int arg_endindex (struct arg_hdr**) ; 
 int /*<<< orphan*/  arg_parse_check (struct arg_hdr**,struct arg_end*) ; 
 int /*<<< orphan*/  arg_parse_tagged (int,char**,struct arg_hdr**,struct arg_end*) ; 
 int /*<<< orphan*/  arg_parse_untagged (int,char**,struct arg_hdr**,struct arg_end*) ; 
 int /*<<< orphan*/  arg_register_error (struct arg_end*,struct arg_end*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arg_reset (void**) ; 
 int /*<<< orphan*/  free (char**) ; 
 scalar_t__ malloc (int) ; 

int arg_parse(int argc, char * *argv, void * *argtable)
{
    struct arg_hdr * *table = (struct arg_hdr * *)argtable;
    struct arg_end *endtable;
    int endindex;
    char * *argvcopy = NULL;

    /*printf("arg_parse(%d,%p,%p)\n",argc,argv,argtable);*/

    /* reset any argtable data from previous invocations */
    arg_reset(argtable);

    /* locate the first end-of-table marker within the array */
    endindex = arg_endindex(table);
    endtable = (struct arg_end *)table[endindex];

    /* Special case of argc==0.  This can occur on Texas Instruments DSP. */
    /* Failure to trap this case results in an unwanted NULL result from  */
    /* the malloc for argvcopy (next code block).                         */
    if (argc == 0)
    {
        /* We must still perform post-parse checks despite the absence of command line arguments */
        arg_parse_check(table, endtable);

        /* Now we are finished */
        return endtable->count;
    }

    argvcopy = (char **)malloc(sizeof(char *) * (argc + 1));
    if (argvcopy)
    {
        int i;

        /*
           Fill in the local copy of argv[]. We need a local copy
           because getopt rearranges argv[] which adversely affects
           susbsequent parsing attempts.
         */
        for (i = 0; i < argc; i++)
            argvcopy[i] = argv[i];

        argvcopy[argc] = NULL;
        
        /* parse the command line (local copy) for tagged options */
        arg_parse_tagged(argc, argvcopy, table, endtable);

        /* parse the command line (local copy) for untagged options */
        arg_parse_untagged(argc, argvcopy, table, endtable);

        /* if no errors so far then perform post-parse checks otherwise dont bother */
        if (endtable->count == 0)
            arg_parse_check(table, endtable);

        /* release the local copt of argv[] */
        free(argvcopy);
    }
    else
    {
        /* memory alloc failed */
        arg_register_error(endtable, endtable, ARG_EMALLOC, NULL);
    }

    return endtable->count;
}