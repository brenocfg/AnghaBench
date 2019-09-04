#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pw_shell; int /*<<< orphan*/  pw_dir; int /*<<< orphan*/  pw_gecos; int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_uid; int /*<<< orphan*/  pw_passwd; int /*<<< orphan*/  pw_name; } ;
struct TYPE_3__ {int /*<<< orphan*/  shell; int /*<<< orphan*/  dir; int /*<<< orphan*/  gecos; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  password; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_2__ __tmp_passwd ; 
 TYPE_1__ myos_pass ; 

void build_tmp_passwd(){
	__tmp_passwd.pw_name=myos_pass.name;
	__tmp_passwd.pw_passwd=myos_pass.password;
	__tmp_passwd.pw_uid=myos_pass.uid;
	__tmp_passwd.pw_gid=myos_pass.gid;
	__tmp_passwd.pw_gecos=myos_pass.gecos;
	__tmp_passwd.pw_dir=myos_pass.dir;
	__tmp_passwd.pw_shell=myos_pass.shell;
}