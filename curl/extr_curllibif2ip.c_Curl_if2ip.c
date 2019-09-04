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
typedef  int /*<<< orphan*/  if2ip_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  IF2IP_NOT_FOUND ; 

if2ip_result_t Curl_if2ip(int af, unsigned int remote_scope,
                          unsigned int local_scope_id, const char *interf,
                          char *buf, int buf_size)
{
    (void) af;
    (void) remote_scope;
    (void) local_scope_id;
    (void) interf;
    (void) buf;
    (void) buf_size;
    return IF2IP_NOT_FOUND;
}