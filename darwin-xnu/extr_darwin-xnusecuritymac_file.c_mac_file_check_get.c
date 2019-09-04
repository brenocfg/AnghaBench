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
struct ucred {int dummy; } ;
struct fileglob {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,struct ucred*,struct fileglob*,char*,int) ; 
 int /*<<< orphan*/  file_check_get ; 

int
mac_file_check_get(struct ucred *cred, struct fileglob *fg, char *elements,
    int len)
{
	int error;
	
	MAC_CHECK(file_check_get, cred, fg, elements, len);
	return (error);
}