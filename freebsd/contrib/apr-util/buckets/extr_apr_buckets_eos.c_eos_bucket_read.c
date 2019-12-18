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
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_read_type_e ;
typedef  int /*<<< orphan*/  apr_bucket ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 

__attribute__((used)) static apr_status_t eos_bucket_read(apr_bucket *b, const char **str, 
                                    apr_size_t *len, apr_read_type_e block)
{
    *str = NULL;
    *len = 0;
    return APR_SUCCESS;
}