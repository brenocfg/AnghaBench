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
struct binary {int /*<<< orphan*/  arch; } ;

/* Variables and functions */
 struct binary** bin_list ; 
 int bin_list_len ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

struct binary *binary_get_by_arch(char *arch)
{
    int i;

    for (i = 0; i < bin_list_len; i++)
    {
        if (strcmp(arch, bin_list[i]->arch) == 0)
            return bin_list[i];
    }

    return NULL;
}