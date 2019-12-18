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
struct TYPE_3__ {int /*<<< orphan*/  nfailures; } ;
typedef  TYPE_1__ SRunner ;

/* Variables and functions */
 int CK_VERBOSE ; 
 char* _check_current_filename ; 
 char* _check_current_function ; 
 int _check_current_lineno ; 
 int /*<<< orphan*/  printf (char*,char*,int,char*) ; 

__attribute__((used)) static void
add_failure(SRunner *runner, int verbosity)
{
    runner->nfailures++;
    if (verbosity >= CK_VERBOSE) {
        printf("%s:%d: %s\n", _check_current_filename,
               _check_current_lineno, _check_current_function);
    }
}