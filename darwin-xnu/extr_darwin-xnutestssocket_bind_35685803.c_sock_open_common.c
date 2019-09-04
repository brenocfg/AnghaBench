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
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int,char*,int,int) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int socket (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sock_open_common(int pf, int type)
{
	int 	s;

	s = socket(pf, type, 0);
	T_QUIET;
	T_ASSERT_POSIX_SUCCESS(s, "socket(%d, %d, 0)", pf, type);
	return (s);
}