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
 char const*** hb_x264_encopt_synonyms ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

const char * hb_x264_encopt_name(const char *name)
{
    int i;
    for (i = 0; hb_x264_encopt_synonyms[i][0] != NULL; i++)
        if (!strcmp(name, hb_x264_encopt_synonyms[i][1]))
            return hb_x264_encopt_synonyms[i][0];
    return name;
}