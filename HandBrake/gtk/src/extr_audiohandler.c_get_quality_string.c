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
typedef  int /*<<< orphan*/  gdouble ;

/* Variables and functions */
 char* ghb_format_quality (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char * get_quality_string(int codec, gdouble quality)
{
    char *s_quality = ghb_format_quality("", codec, quality);
    return s_quality;
}