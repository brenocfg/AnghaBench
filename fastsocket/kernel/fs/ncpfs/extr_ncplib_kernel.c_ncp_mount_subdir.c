#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* mounted_vol; } ;
struct ncp_server {int* name_space; TYPE_1__ m; } ;
typedef  size_t __u8 ;
typedef  size_t __u32 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int ncp_ObtainSpecificDirBase (struct ncp_server*,size_t,int,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ncp_get_known_namespace (struct ncp_server*,size_t) ; 

int
ncp_mount_subdir(struct ncp_server *server,
		 __u8 volNumber, __u8 srcNS, __le32 dirEntNum,
		 __u32* volume, __le32* newDirEnt, __le32* newDosEnt)
{
	int dstNS;
	int result;
	
	dstNS = ncp_get_known_namespace(server, volNumber);
	if ((result = ncp_ObtainSpecificDirBase(server, srcNS, dstNS, volNumber, 
				      dirEntNum, NULL, newDirEnt, newDosEnt)) != 0)
	{
		return result;
	}
	server->name_space[volNumber] = dstNS;
	*volume = volNumber;
	server->m.mounted_vol[1] = 0;
	server->m.mounted_vol[0] = 'X';
	return 0;
}