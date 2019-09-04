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
struct TYPE_3__ {char* my_name; char* test_name; int /*<<< orphan*/ * test_argv; scalar_t__ test_argc; int /*<<< orphan*/  length; int /*<<< orphan*/  num_threads; } ;
typedef  TYPE_1__ parsed_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  strtoll (char*,int /*<<< orphan*/ *,int) ; 

int parse_args(int argc, char** argv, parsed_args_t* parsed_args) {
    if(argc != 4) {
        return -1;
    }

    parsed_args->my_name = argv[0];
    parsed_args->test_name = argv[1];
    parsed_args->num_threads = atoi(argv[2]);
    parsed_args->length = strtoll(argv[3], NULL, 10);
    parsed_args->test_argc = 0;
    parsed_args->test_argv = NULL;
    return 0;
}