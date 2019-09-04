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
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int avpriv_io_delete (char const*) ; 

__attribute__((used)) static int del_op(const char *url)
{
    int ret = avpriv_io_delete(url);
    if (ret < 0)
        av_log(NULL, AV_LOG_ERROR, "Cannot delete '%s': %s.\n", url, av_err2str(ret));
    return ret;
}