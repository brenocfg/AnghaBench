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
struct passwd {char* pw_name; char* pw_passwd; int pw_gid; char* pw_gecos; char* pw_dir; char* pw_shell; int /*<<< orphan*/  pw_uid; } ;

/* Variables and functions */
 struct passwd out ; 

struct passwd* getpwuid(uid_t uid)
{
   out.pw_name = "retroarch";
   out.pw_passwd = "Wait, what?";
   out.pw_uid = uid;
   out.pw_gid = 1000;
   out.pw_gecos = "retroarch";
   out.pw_dir = "sd:/";
   out.pw_shell = "/vol/system_slc/fw.img";

   return &out;
}