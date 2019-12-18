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
struct arg_rex {int dummy; } ;

/* Variables and functions */
 struct arg_rex* arg_rexn (char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,int,int,char const*) ; 

struct arg_rex * arg_rex0(const char * shortopts,
                          const char * longopts,
                          const char * pattern,
                          const char *datatype,
                          int flags,
                          const char *glossary)
{
    return arg_rexn(shortopts,
                    longopts,
                    pattern,
                    datatype,
                    0,
                    1,
                    flags,
                    glossary);
}