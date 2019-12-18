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
typedef  int /*<<< orphan*/  enable ;

/* Variables and functions */
 int /*<<< orphan*/  SRTO_RCVSYN ; 
 int /*<<< orphan*/  SRTO_SNDSYN ; 
 int srt_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int libsrt_socket_nonblock(int socket, int enable)
{
    int ret = srt_setsockopt(socket, 0, SRTO_SNDSYN, &enable, sizeof(enable));
    if (ret < 0)
        return ret;
    return srt_setsockopt(socket, 0, SRTO_RCVSYN, &enable, sizeof(enable));
}