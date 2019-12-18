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
struct net_device {struct claw_privbk* ml_priv; } ;
struct claw_privbk {struct claw_env* p_env; } ;
struct claw_env {int packing; int /*<<< orphan*/  api_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAW_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
#define  DO_PACKED 130 
 int EINVAL ; 
 int /*<<< orphan*/  HOST_APPL_NAME ; 
#define  PACKING_ASK 129 
#define  PACK_SEND 128 
 int /*<<< orphan*/  WS_APPL_NAME_IP_NAME ; 
 int /*<<< orphan*/  WS_APPL_NAME_PACKED ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  setup ; 

__attribute__((used)) static int
find_link(struct net_device *dev, char *host_name, char *ws_name )
{
	struct claw_privbk *privptr;
	struct claw_env *p_env;
	int    rc=0;

	CLAW_DBF_TEXT(2, setup, "findlink");
	privptr = dev->ml_priv;
        p_env=privptr->p_env;
	switch (p_env->packing)
	{
		case  PACKING_ASK:
			if ((memcmp(WS_APPL_NAME_PACKED, host_name, 8)!=0) ||
			    (memcmp(WS_APPL_NAME_PACKED, ws_name, 8)!=0 ))
        	             rc = EINVAL;
			break;
		case  DO_PACKED:
		case  PACK_SEND:
			if ((memcmp(WS_APPL_NAME_IP_NAME, host_name, 8)!=0) ||
			    (memcmp(WS_APPL_NAME_IP_NAME, ws_name, 8)!=0 ))
        	        	rc = EINVAL;
			break;
		default:
	       		if ((memcmp(HOST_APPL_NAME, host_name, 8)!=0) ||
		    	    (memcmp(p_env->api_type , ws_name, 8)!=0))
        	        	rc = EINVAL;
			break;
	}

	return rc;
}