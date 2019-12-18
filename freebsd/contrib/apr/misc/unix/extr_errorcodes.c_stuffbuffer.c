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
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr_cpystrn (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *stuffbuffer(char *buf, apr_size_t bufsize, const char *s)
{
    apr_cpystrn(buf,s,bufsize);
    return buf;
}