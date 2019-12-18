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
struct concap_proto {TYPE_1__* net_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IX25DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isdn_net_hangup (TYPE_1__*) ; 

__attribute__((used)) static int isdn_concap_dl_disconn_req(struct concap_proto *concap)
{
	IX25DEBUG( "isdn_concap_dl_disconn_req: %s \n", concap -> net_dev -> name);

	isdn_net_hangup( concap -> net_dev );
	return 0;
}