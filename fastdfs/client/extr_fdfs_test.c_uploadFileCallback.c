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
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  g_fdfs_network_timeout ; 
 int tcpsendfile (int,char*,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int uploadFileCallback(void *arg, const int64_t file_size, int sock)
{
	int64_t total_send_bytes;
	char *filename;

	if (arg == NULL)
	{
		return EINVAL;
	}

	filename = (char *)arg;
	return tcpsendfile(sock, filename, file_size, \
		g_fdfs_network_timeout, &total_send_bytes);
}