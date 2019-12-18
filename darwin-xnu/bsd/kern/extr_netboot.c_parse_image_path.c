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
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  parse_booter_path (char*,struct in_addr*,char const**,char**,char**) ; 
 int /*<<< orphan*/  parse_netboot_path (char*,struct in_addr*,char const**,char**,char**) ; 

__attribute__((used)) static boolean_t
parse_image_path(char * path, struct in_addr * iaddr_p, char const * * host,
		 char * * mount_dir, char * * image_path)
{
    if (path[0] >= '0' && path[0] <= '9') {
	return (parse_booter_path(path, iaddr_p, host, mount_dir,
				  image_path));
    }
    return (parse_netboot_path(path, iaddr_p, host, mount_dir,
			       image_path));
}