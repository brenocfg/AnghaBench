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
 int /*<<< orphan*/  SEV_ERROR ; 
 int /*<<< orphan*/  ZBAR_ERR_UNSUPPORTED ; 
 int err_capture (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char*) ; 

__attribute__((used)) static inline int null_error (void *m,
                              const char *func)
{
    return(err_capture(m, SEV_ERROR, ZBAR_ERR_UNSUPPORTED, func,
                       "not compiled with video input support"));
}