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
 int /*<<< orphan*/  attach_master ; 
 int /*<<< orphan*/  attach_slave ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader ; 
 int /*<<< orphan*/  writer ; 
 int writing ; 

__attribute__((used)) static void
join_threads(void)
{
	close(attach_slave);
	close(attach_master);
	writing = false;
	pthread_join(reader, NULL);
	pthread_join(writer, NULL);
}