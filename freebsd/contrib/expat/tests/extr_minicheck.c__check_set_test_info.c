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
 char const* _check_current_filename ; 
 char const* _check_current_function ; 
 int _check_current_lineno ; 

void
_check_set_test_info(char const *function, char const *filename, int lineno)
{
    _check_current_function = function;
    _check_current_lineno = lineno;
    _check_current_filename = filename;
}