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
struct TYPE_3__ {void* on_fail; } ;
typedef  TYPE_1__ TeeSlave ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 void* DEFAULT_SLAVE_FAILURE_POLICY ; 
 int /*<<< orphan*/  EINVAL ; 
 void* ON_SLAVE_FAILURE_ABORT ; 
 void* ON_SLAVE_FAILURE_IGNORE ; 
 int /*<<< orphan*/  av_strcasecmp (char*,char const*) ; 

__attribute__((used)) static inline int parse_slave_failure_policy_option(const char *opt, TeeSlave *tee_slave)
{
    if (!opt) {
        tee_slave->on_fail = DEFAULT_SLAVE_FAILURE_POLICY;
        return 0;
    } else if (!av_strcasecmp("abort", opt)) {
        tee_slave->on_fail = ON_SLAVE_FAILURE_ABORT;
        return 0;
    } else if (!av_strcasecmp("ignore", opt)) {
        tee_slave->on_fail = ON_SLAVE_FAILURE_IGNORE;
        return 0;
    }
    /* Set failure behaviour to abort, so invalid option error will not be ignored */
    tee_slave->on_fail = ON_SLAVE_FAILURE_ABORT;
    return AVERROR(EINVAL);
}