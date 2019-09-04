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
typedef  int /*<<< orphan*/  uid_t ;
struct passwd {int dummy; } ;
typedef  int /*<<< orphan*/  passwd_myos ;

/* Variables and functions */
 struct passwd __tmp_passwd ; 
 int /*<<< orphan*/  build_tmp_passwd () ; 
 int /*<<< orphan*/ * myos_user_getID (int /*<<< orphan*/ ) ; 

struct passwd* getpwuid( uid_t uid ) {

	passwd_myos* pass=myos_user_getID(uid);
	if (pass==NULL)
		return NULL;
	
	build_tmp_passwd();
	return &__tmp_passwd;
}