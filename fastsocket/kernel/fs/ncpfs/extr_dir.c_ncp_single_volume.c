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
struct ncp_server {TYPE_1__ m; } ;

/* Variables and functions */

__attribute__((used)) static inline int
ncp_single_volume(struct ncp_server *server)
{
	return (server->m.mounted_vol[0] != '\0');
}