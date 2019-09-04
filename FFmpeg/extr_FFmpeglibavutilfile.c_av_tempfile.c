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
 int avpriv_tempfile (char const*,char**,int,void*) ; 

int av_tempfile(const char *prefix, char **filename, int log_offset, void *log_ctx) {
    return avpriv_tempfile(prefix, filename, log_offset, log_ctx);
}