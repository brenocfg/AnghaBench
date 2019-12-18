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
typedef  int /*<<< orphan*/  apr_strmatch_pattern ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */

__attribute__((used)) static const char *match_no_op(const apr_strmatch_pattern *this_pattern,
                               const char *s, apr_size_t slen)
{
    return s;
}