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
struct arg_lit {int dummy; } ;

/* Variables and functions */
 struct arg_lit* arg_litn (char const*,char const*,int,int,char const*) ; 

struct arg_lit * arg_lit1(
    const char *shortopts,
    const char *longopts,
    const char *glossary)
{
    return arg_litn(shortopts, longopts, 1, 1, glossary);
}